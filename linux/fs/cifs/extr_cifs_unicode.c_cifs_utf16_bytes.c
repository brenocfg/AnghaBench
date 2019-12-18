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
 int /*<<< orphan*/  NO_MAP_UNI_RSVD ; 
 int cifs_mapchar (char*,scalar_t__*,struct nls_table const*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_unaligned_le16 (int /*<<< orphan*/  const*) ; 

int
cifs_utf16_bytes(const __le16 *from, int maxbytes,
		const struct nls_table *codepage)
{
	int i;
	int charlen, outlen = 0;
	int maxwords = maxbytes / 2;
	char tmp[NLS_MAX_CHARSET_SIZE];
	__u16 ftmp[3];

	for (i = 0; i < maxwords; i++) {
		ftmp[0] = get_unaligned_le16(&from[i]);
		if (ftmp[0] == 0)
			break;
		if (i + 1 < maxwords)
			ftmp[1] = get_unaligned_le16(&from[i + 1]);
		else
			ftmp[1] = 0;
		if (i + 2 < maxwords)
			ftmp[2] = get_unaligned_le16(&from[i + 2]);
		else
			ftmp[2] = 0;

		charlen = cifs_mapchar(tmp, ftmp, codepage, NO_MAP_UNI_RSVD);
		outlen += charlen;
	}

	return outlen;
}