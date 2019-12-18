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
struct nls_table {int dummy; } ;
typedef  scalar_t__ __u16 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int NLS_MAX_CHARSET_SIZE ; 
 int cifs_mapchar (char*,scalar_t__*,struct nls_table const*,int) ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/  const*) ; 
 int nls_nullsize (struct nls_table const*) ; 

int
cifs_from_utf16(char *to, const __le16 *from, int tolen, int fromlen,
		const struct nls_table *codepage, int map_type)
{
	int i, charlen, safelen;
	int outlen = 0;
	int nullsize = nls_nullsize(codepage);
	int fromwords = fromlen / 2;
	char tmp[NLS_MAX_CHARSET_SIZE];
	__u16 ftmp[3];		/* ftmp[3] = 3array x 2bytes = 6bytes UTF-16 */

	/*
	 * because the chars can be of varying widths, we need to take care
	 * not to overflow the destination buffer when we get close to the
	 * end of it. Until we get to this offset, we don't need to check
	 * for overflow however.
	 */
	safelen = tolen - (NLS_MAX_CHARSET_SIZE + nullsize);

	for (i = 0; i < fromwords; i++) {
		ftmp[0] = get_unaligned_le16(&from[i]);
		if (ftmp[0] == 0)
			break;
		if (i + 1 < fromwords)
			ftmp[1] = get_unaligned_le16(&from[i + 1]);
		else
			ftmp[1] = 0;
		if (i + 2 < fromwords)
			ftmp[2] = get_unaligned_le16(&from[i + 2]);
		else
			ftmp[2] = 0;

		/*
		 * check to see if converting this character might make the
		 * conversion bleed into the null terminator
		 */
		if (outlen >= safelen) {
			charlen = cifs_mapchar(tmp, ftmp, codepage, map_type);
			if ((outlen + charlen) > (tolen - nullsize))
				break;
		}

		/* put converted char into 'to' buffer */
		charlen = cifs_mapchar(&to[outlen], ftmp, codepage, map_type);
		outlen += charlen;

		/* charlen (=bytes of UTF-8 for 1 character)
		 * 4bytes UTF-8(surrogate pair) is charlen=4
		 *   (4bytes UTF-16 code)
		 * 7-8bytes UTF-8(IVS) is charlen=3+4 or 4+4
		 *   (2 UTF-8 pairs divided to 2 UTF-16 pairs) */
		if (charlen == 4)
			i++;
		else if (charlen >= 5)
			/* 5-6bytes UTF-8 */
			i += 2;
	}

	/* properly null-terminate string */
	for (i = 0; i < nullsize; i++)
		to[outlen++] = 0;

	return outlen;
}