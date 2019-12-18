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
struct nls_table {int (* char2uni ) (char const*,int,int*) ;int /*<<< orphan*/  charset; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  UTF16_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,char const,int) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int stub1 (char const*,int,int*) ; 
 int utf8s_to_utf16s (char const*,int,int /*<<< orphan*/ ,int*,int) ; 

int
cifs_strtoUTF16(__le16 *to, const char *from, int len,
	      const struct nls_table *codepage)
{
	int charlen;
	int i;
	wchar_t wchar_to; /* needed to quiet sparse */

	/* special case for utf8 to handle no plane0 chars */
	if (!strcmp(codepage->charset, "utf8")) {
		/*
		 * convert utf8 -> utf16, we assume we have enough space
		 * as caller should have assumed conversion does not overflow
		 * in destination len is length in wchar_t units (16bits)
		 */
		i  = utf8s_to_utf16s(from, len, UTF16_LITTLE_ENDIAN,
				       (wchar_t *) to, len);

		/* if success terminate and exit */
		if (i >= 0)
			goto success;
		/*
		 * if fails fall back to UCS encoding as this
		 * function should not return negative values
		 * currently can fail only if source contains
		 * invalid encoded characters
		 */
	}

	for (i = 0; len && *from; i++, from += charlen, len -= charlen) {
		charlen = codepage->char2uni(from, len, &wchar_to);
		if (charlen < 1) {
			cifs_dbg(VFS, "strtoUTF16: char2uni of 0x%x returned %d\n",
				 *from, charlen);
			/* A question mark */
			wchar_to = 0x003f;
			charlen = 1;
		}
		put_unaligned_le16(wchar_to, &to[i]);
	}

success:
	put_unaligned_le16(0, &to[i]);
	return i;
}