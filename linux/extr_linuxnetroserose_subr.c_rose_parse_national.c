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
struct rose_facilities_struct {unsigned char rand; int source_ndigis; int dest_ndigis; int /*<<< orphan*/ * source_digis; int /*<<< orphan*/ * dest_digis; int /*<<< orphan*/  fail_addr; int /*<<< orphan*/  fail_call; } ;

/* Variables and functions */
 unsigned char AX25_ADDR_LEN ; 
 unsigned char AX25_HBIT ; 
 unsigned char FAC_NATIONAL_DEST_DIGI ; 
 unsigned char FAC_NATIONAL_DIGIS ; 
 unsigned char FAC_NATIONAL_FAIL_ADD ; 
 unsigned char FAC_NATIONAL_FAIL_CALL ; 
 unsigned char FAC_NATIONAL_RAND ; 
 unsigned char FAC_NATIONAL_SRC_DIGI ; 
 unsigned char ROSE_ADDR_LEN ; 
 int ROSE_MAX_DIGIS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,unsigned char) ; 

__attribute__((used)) static int rose_parse_national(unsigned char *p, struct rose_facilities_struct *facilities, int len)
{
	unsigned char *pt;
	unsigned char l, lg, n = 0;
	int fac_national_digis_received = 0;

	do {
		switch (*p & 0xC0) {
		case 0x00:
			if (len < 2)
				return -1;
			p   += 2;
			n   += 2;
			len -= 2;
			break;

		case 0x40:
			if (len < 3)
				return -1;
			if (*p == FAC_NATIONAL_RAND)
				facilities->rand = ((p[1] << 8) & 0xFF00) + ((p[2] << 0) & 0x00FF);
			p   += 3;
			n   += 3;
			len -= 3;
			break;

		case 0x80:
			if (len < 4)
				return -1;
			p   += 4;
			n   += 4;
			len -= 4;
			break;

		case 0xC0:
			if (len < 2)
				return -1;
			l = p[1];
			if (len < 2 + l)
				return -1;
			if (*p == FAC_NATIONAL_DEST_DIGI) {
				if (!fac_national_digis_received) {
					if (l < AX25_ADDR_LEN)
						return -1;
					memcpy(&facilities->source_digis[0], p + 2, AX25_ADDR_LEN);
					facilities->source_ndigis = 1;
				}
			}
			else if (*p == FAC_NATIONAL_SRC_DIGI) {
				if (!fac_national_digis_received) {
					if (l < AX25_ADDR_LEN)
						return -1;
					memcpy(&facilities->dest_digis[0], p + 2, AX25_ADDR_LEN);
					facilities->dest_ndigis = 1;
				}
			}
			else if (*p == FAC_NATIONAL_FAIL_CALL) {
				if (l < AX25_ADDR_LEN)
					return -1;
				memcpy(&facilities->fail_call, p + 2, AX25_ADDR_LEN);
			}
			else if (*p == FAC_NATIONAL_FAIL_ADD) {
				if (l < 1 + ROSE_ADDR_LEN)
					return -1;
				memcpy(&facilities->fail_addr, p + 3, ROSE_ADDR_LEN);
			}
			else if (*p == FAC_NATIONAL_DIGIS) {
				if (l % AX25_ADDR_LEN)
					return -1;
				fac_national_digis_received = 1;
				facilities->source_ndigis = 0;
				facilities->dest_ndigis   = 0;
				for (pt = p + 2, lg = 0 ; lg < l ; pt += AX25_ADDR_LEN, lg += AX25_ADDR_LEN) {
					if (pt[6] & AX25_HBIT) {
						if (facilities->dest_ndigis >= ROSE_MAX_DIGIS)
							return -1;
						memcpy(&facilities->dest_digis[facilities->dest_ndigis++], pt, AX25_ADDR_LEN);
					} else {
						if (facilities->source_ndigis >= ROSE_MAX_DIGIS)
							return -1;
						memcpy(&facilities->source_digis[facilities->source_ndigis++], pt, AX25_ADDR_LEN);
					}
				}
			}
			p   += l + 2;
			n   += l + 2;
			len -= l + 2;
			break;
		}
	} while (*p != 0x00 && len > 0);

	return n;
}