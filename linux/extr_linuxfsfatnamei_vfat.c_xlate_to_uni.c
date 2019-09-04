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
typedef  int wchar_t ;
typedef  int u8 ;
struct nls_table {int (* char2uni ) (unsigned char const*,int,int*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int FAT_LFN_LEN ; 
 int /*<<< orphan*/  UTF16_HOST_ENDIAN ; 
 scalar_t__ hex2bin (int*,unsigned char const*,int) ; 
 int stub1 (unsigned char const*,int,int*) ; 
 int utf8s_to_utf16s (unsigned char const*,int,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
xlate_to_uni(const unsigned char *name, int len, unsigned char *outname,
	     int *longlen, int *outlen, int escape, int utf8,
	     struct nls_table *nls)
{
	const unsigned char *ip;
	unsigned char *op;
	int i, fill;
	int charlen;

	if (utf8) {
		*outlen = utf8s_to_utf16s(name, len, UTF16_HOST_ENDIAN,
				(wchar_t *) outname, FAT_LFN_LEN + 2);
		if (*outlen < 0)
			return *outlen;
		else if (*outlen > FAT_LFN_LEN)
			return -ENAMETOOLONG;

		op = &outname[*outlen * sizeof(wchar_t)];
	} else {
		for (i = 0, ip = name, op = outname, *outlen = 0;
			 i < len && *outlen < FAT_LFN_LEN;
			 *outlen += 1) {
			if (escape && (*ip == ':')) {
				u8 uc[2];

				if (i > len - 5)
					return -EINVAL;

				if (hex2bin(uc, ip + 1, 2) < 0)
					return -EINVAL;

				*(wchar_t *)op = uc[0] << 8 | uc[1];

				op += 2;
				ip += 5;
				i += 5;
			} else {
				charlen = nls->char2uni(ip, len - i,
							(wchar_t *)op);
				if (charlen < 0)
					return -EINVAL;
				ip += charlen;
				i += charlen;
				op += 2;
			}
		}
		if (i < len)
			return -ENAMETOOLONG;
	}

	*longlen = *outlen;
	if (*outlen % 13) {
		*op++ = 0;
		*op++ = 0;
		*outlen += 1;
		if (*outlen % 13) {
			fill = 13 - (*outlen % 13);
			for (i = 0; i < fill; i++) {
				*op++ = 0xff;
				*op++ = 0xff;
			}
			*outlen += fill;
		}
	}

	return 0;
}