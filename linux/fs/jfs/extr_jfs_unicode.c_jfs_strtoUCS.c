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
typedef  scalar_t__ wchar_t ;
struct nls_table {int (* char2uni ) (unsigned char const*,int,scalar_t__*) ;int /*<<< orphan*/  charset; } ;

/* Variables and functions */
 int /*<<< orphan*/  jfs_err (char*,int,...) ; 
 int stub1 (unsigned char const*,int,scalar_t__*) ; 

__attribute__((used)) static int jfs_strtoUCS(wchar_t * to, const unsigned char *from, int len,
		struct nls_table *codepage)
{
	int charlen;
	int i;

	if (codepage) {
		for (i = 0; len && *from; i++, from += charlen, len -= charlen)
		{
			charlen = codepage->char2uni(from, len, &to[i]);
			if (charlen < 1) {
				jfs_err("jfs_strtoUCS: char2uni returned %d.",
					charlen);
				jfs_err("charset = %s, char = 0x%x",
					codepage->charset, *from);
				return charlen;
			}
		}
	} else {
		for (i = 0; (i < len) && from[i]; i++)
			to[i] = (wchar_t) from[i];
	}

	to[i] = 0;
	return i;
}