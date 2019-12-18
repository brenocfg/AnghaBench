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
struct cpio_data {char* member_2; unsigned int size; void* data; int /*<<< orphan*/  name; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 size_t C_FILESIZE ; 
 size_t C_MAGIC ; 
 size_t C_MODE ; 
 size_t C_NAMESIZE ; 
 int C_NFIELDS ; 
 unsigned int MAX_CPIO_FILE_NAME ; 
 char* PTR_ALIGN (char const*,int) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,unsigned int) ; 
 size_t strlen (char const*) ; 

struct cpio_data find_cpio_data(const char *path, void *data,
				size_t len,  long *nextoff)
{
	const size_t cpio_header_len = 8*C_NFIELDS - 2;
	struct cpio_data cd = { NULL, 0, "" };
	const char *p, *dptr, *nptr;
	unsigned int ch[C_NFIELDS], *chp, v;
	unsigned char c, x;
	size_t mypathsize = strlen(path);
	int i, j;

	p = data;

	while (len > cpio_header_len) {
		if (!*p) {
			/* All cpio headers need to be 4-byte aligned */
			p += 4;
			len -= 4;
			continue;
		}

		j = 6;		/* The magic field is only 6 characters */
		chp = ch;
		for (i = C_NFIELDS; i; i--) {
			v = 0;
			while (j--) {
				v <<= 4;
				c = *p++;

				x = c - '0';
				if (x < 10) {
					v += x;
					continue;
				}

				x = (c | 0x20) - 'a';
				if (x < 6) {
					v += x + 10;
					continue;
				}

				goto quit; /* Invalid hexadecimal */
			}
			*chp++ = v;
			j = 8;	/* All other fields are 8 characters */
		}

		if ((ch[C_MAGIC] - 0x070701) > 1)
			goto quit; /* Invalid magic */

		len -= cpio_header_len;

		dptr = PTR_ALIGN(p + ch[C_NAMESIZE], 4);
		nptr = PTR_ALIGN(dptr + ch[C_FILESIZE], 4);

		if (nptr > p + len || dptr < p || nptr < dptr)
			goto quit; /* Buffer overrun */

		if ((ch[C_MODE] & 0170000) == 0100000 &&
		    ch[C_NAMESIZE] >= mypathsize &&
		    !memcmp(p, path, mypathsize)) {

			if (nextoff)
				*nextoff = (long)nptr - (long)data;

			if (ch[C_NAMESIZE] - mypathsize >= MAX_CPIO_FILE_NAME) {
				pr_warn(
				"File %s exceeding MAX_CPIO_FILE_NAME [%d]\n",
				p, MAX_CPIO_FILE_NAME);
			}
			strlcpy(cd.name, p + mypathsize, MAX_CPIO_FILE_NAME);

			cd.data = (void *)dptr;
			cd.size = ch[C_FILESIZE];
			return cd; /* Found it! */
		}
		len -= (nptr - p);
		p = nptr;
	}

quit:
	return cd;
}