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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cifsConvertToUTF16 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct nls_table const*,int) ; 
 int cifs_local_to_utf16_bytes (char const*,int const,struct nls_table const*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__le16 *
cifs_strndup_to_utf16(const char *src, const int maxlen, int *utf16_len,
		      const struct nls_table *cp, int remap)
{
	int len;
	__le16 *dst;

	len = cifs_local_to_utf16_bytes(src, maxlen, cp);
	len += 2; /* NULL */
	dst = kmalloc(len, GFP_KERNEL);
	if (!dst) {
		*utf16_len = 0;
		return NULL;
	}
	cifsConvertToUTF16(dst, src, strlen(src), cp, remap);
	*utf16_len = len;
	return dst;
}