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
typedef  int /*<<< orphan*/  wchar_t ;
struct nls_table {int (* char2uni ) (char const*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cifs_local_to_utf16_bytes(const char *from, int len,
			  const struct nls_table *codepage)
{
	int charlen;
	int i;
	wchar_t wchar_to;

	for (i = 0; len && *from; i++, from += charlen, len -= charlen) {
		charlen = codepage->char2uni(from, len, &wchar_to);
		/* Failed conversion defaults to a question mark */
		if (charlen < 1)
			charlen = 1;
	}
	return 2 * i; /* UTF16 characters are two bytes */
}