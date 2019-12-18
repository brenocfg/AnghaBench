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
typedef  int /*<<< orphan*/  text ;

/* Variables and functions */
 scalar_t__ VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cstring_to_text (char*) ; 
 int /*<<< orphan*/  pfree (unsigned char*) ; 
 unsigned char* pg_do_encoding_conversion (unsigned char*,int,int,int) ; 

__attribute__((used)) static text *
convert_charset(text *src, int cset_from, int cset_to)
{
	int			src_len = VARSIZE_ANY_EXHDR(src);
	unsigned char *dst;
	unsigned char *csrc = (unsigned char *) VARDATA_ANY(src);
	text	   *res;

	dst = pg_do_encoding_conversion(csrc, src_len, cset_from, cset_to);
	if (dst == csrc)
		return src;

	res = cstring_to_text((char *) dst);
	pfree(dst);
	return res;
}