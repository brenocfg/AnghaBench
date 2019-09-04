#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ut8 ;
typedef  int ut32 ;
typedef  int ut16 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int INT_MAX ; 
 int UT16_MAX ; 
 int* calloc (int,int const) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (int*) ; 
 int r_buf_write_at (int /*<<< orphan*/ *,int,int*,int) ; 
 int sscanf (char*,char*,int*,...) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static bool ihex_parse(RBuffer *rbuf, char *str) {
	ut8 *sec_tmp;
	ut32 sec_start = 0;	//addr for next section write
	ut32 segreg = 0;	//basis for addr fields
	ut32 addr_tmp = 0;	//addr for record
	ut16 next_addr = 0;	//for checking if records are sequential
	char *eol;
	ut8 cksum;
	int extH, extL;
	int bc = 0, type, byte, i, l;
	//fugly macro to prevent an overflow of r_buf_write_at() len
#define SEC_MAX (sec_size < INT_MAX)? sec_size: INT_MAX
	ut32 sec_size = 0;
	const int sec_count = UT16_MAX;
	sec_tmp = calloc (1, sec_count);
	if (!sec_tmp) {
		goto fail;
	}
	do {
		l = sscanf (str, ":%02x%04x%02x", &bc, &addr_tmp, &type);
		if (l != 3) {
			eprintf ("Invalid data in ihex file (%.*s)\n", 80, str);
			goto fail;
		}
		bc &= 0xff;
		addr_tmp &= 0xffff;
		type &= 0xff;

		switch (type) {
		case 0: // DATA
			eol = strchr (str + 1, ':');
			if (eol) {
				*eol = 0;
			}
			cksum = bc;
			cksum += addr_tmp>>8;
			cksum += addr_tmp;
			cksum += type;

			if ((next_addr != addr_tmp) || ((sec_size + bc) > SEC_MAX)) {
				//previous block is not contiguous, or
				//section buffer is full => write a sparse chunk
				if (sec_size && sec_size < UT16_MAX) {
					if (r_buf_write_at (rbuf, sec_start, sec_tmp, (int) sec_size) != sec_size) {
						eprintf ("sparse buffer problem, giving up\n");
						goto fail;
					}
				}
				//advance cursor, reset section
				sec_start = segreg + addr_tmp;
				next_addr = addr_tmp;
				sec_size = 0;
			}

			for (i = 0; i < bc; i++) {
				if (sscanf (str + 9+ (i*2), "%02x", &byte) !=1) {
					eprintf ("unparsable data !\n");
					goto fail;
				}
				if (sec_size + i < sec_count) {
					sec_tmp[sec_size + i] = (ut8) byte & 0xff;
				}
				cksum += byte;
			}
			sec_size += bc;
			next_addr += bc;
			if (eol) {
				// checksum
				if (sscanf(str+9+(i*2), "%02x", &byte) !=1) {
					eprintf("unparsable data !\n");
					goto fail;
				}
				cksum += byte;
				if (cksum != 0) {
					ut8 fixedcksum = 0-(cksum-byte);
					eprintf ("Checksum failed %02x (got %02x expected %02x)\n",
						cksum, byte, fixedcksum);
					goto fail;
				}
				*eol = ':';
			}
			str = eol;
			break;
		case 1: // EOF. we don't validate checksum here
			if (sec_size) {
				if (r_buf_write_at(rbuf, sec_start, sec_tmp, sec_size) != sec_size) {
					eprintf ("sparse buffer problem, giving up. ssiz=%X, sstart=%X\n", sec_size, sec_start);
					goto fail;
				}
			}
			str = NULL;
			break;
		case 2:	//extended segment record
		case 4:	//extended linear address rec
			//both rec types are handled the same except :
			//	new address = seg_reg <<4 for type 02; new address = lin_addr <<16 for type 04.
			//write current section
			if (sec_size) {
				if (r_buf_write_at(rbuf, sec_start, sec_tmp, sec_size) != sec_size) {
					eprintf("sparse buffer problem, giving up\n");
					goto fail;
				}
			}
			sec_size = 0;

			eol = strchr (str + 1, ':');
			if (eol) {
				*eol = 0;
			}
			cksum = bc;
			cksum += addr_tmp>>8;
			cksum += addr_tmp;
			cksum += type;
			if ((bc != 2) || (addr_tmp != 0)) {
				eprintf ("invalid type 02/04 record!\n");
				goto fail;
			}
			if ((sscanf (str + 9 + 0, "%02x", &extH) !=1) ||
				(sscanf (str + 9 + 2, "%02x", &extL) !=1)) {
				eprintf ("unparsable data !\n");
				goto fail;
			}
			extH &= 0xff;
			extL &= 0xff;
			cksum += extH + extL;

			segreg = extH <<8 | extL;

			//segment rec(02) gives bits 4..19; linear rec(04) is bits 16..31
			segreg = segreg << ((type==2)? 4: 16);
			next_addr = 0;
			sec_start = segreg;

			if (eol) {
				// checksum
				byte=0;	//break checksum if sscanf failed
				if (sscanf (str + 9 + 4, "%02x", &byte) != 1) {
					cksum = 1;
				}
				cksum += byte;
				if (cksum != 0) {
					ut8 fixedcksum = 0-(cksum-byte);
					eprintf ("Checksum failed %02x (got %02x expected %02x)\n",
						cksum, byte, fixedcksum);
					goto fail;
				}
				*eol = ':';
			}
			str = eol;
			break;
		case 3:	//undefined rec. Just skip.
		case 5:	//non-standard, sometimes "start linear adddress"
			str = strchr (str + 1, ':');
			break;
		}
	} while (str);
	free (sec_tmp);
	return true;
fail:
	free (sec_tmp);
	return false;
}