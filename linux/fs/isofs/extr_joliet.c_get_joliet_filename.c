#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct nls_table {int dummy; } ;
struct iso_directory_record {int* name_len; scalar_t__ name; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {unsigned char s_utf8; struct nls_table* s_nls_iocharset; } ;

/* Variables and functions */
 TYPE_1__* ISOFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  UTF16_BIG_ENDIAN ; 
 unsigned char uni16_to_x8 (unsigned char*,int /*<<< orphan*/ *,int,struct nls_table*) ; 
 unsigned char utf16s_to_utf8s (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

int
get_joliet_filename(struct iso_directory_record * de, unsigned char *outname, struct inode * inode)
{
	unsigned char utf8;
	struct nls_table *nls;
	unsigned char len = 0;

	utf8 = ISOFS_SB(inode->i_sb)->s_utf8;
	nls = ISOFS_SB(inode->i_sb)->s_nls_iocharset;

	if (utf8) {
		len = utf16s_to_utf8s((const wchar_t *) de->name,
				de->name_len[0] >> 1, UTF16_BIG_ENDIAN,
				outname, PAGE_SIZE);
	} else {
		len = uni16_to_x8(outname, (__be16 *) de->name,
				de->name_len[0] >> 1, nls);
	}
	if ((len > 2) && (outname[len-2] == ';') && (outname[len-1] == '1'))
		len -= 2;

	/*
	 * Windows doesn't like periods at the end of a name,
	 * so neither do we
	 */
	while (len >= 2 && (outname[len-1] == '.'))
		len--;

	return len;
}