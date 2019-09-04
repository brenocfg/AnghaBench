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
typedef  int /*<<< orphan*/  unichar ;
struct magic_set {int dummy; } ;
struct buffer {int /*<<< orphan*/  flen; int /*<<< orphan*/  fbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int file_ascmagic_with_encoding (struct magic_set*,struct buffer*,int /*<<< orphan*/ *,size_t,char const*,char const*,int) ; 
 scalar_t__ file_encoding (struct magic_set*,struct buffer*,int /*<<< orphan*/ **,size_t*,char const**,char const**,char const**) ; 
 int /*<<< orphan*/  trim_nuls (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
file_ascmagic(struct magic_set *ms, const struct buffer *b, int text)
{
	unichar *ubuf = NULL;
	size_t ulen = 0;
	int rv = 1;
	struct buffer bb;

	const char *code = NULL;
	const char *code_mime = NULL;
	const char *type = NULL;

	bb = *b;
	bb.flen = trim_nuls(b->fbuf, b->flen);

	/* If file doesn't look like any sort of text, give up. */
	if (file_encoding(ms, &bb, &ubuf, &ulen, &code, &code_mime,
	    &type) == 0)
		rv = 0;
        else
		rv = file_ascmagic_with_encoding(ms, &bb,
		    ubuf, ulen, code, type, text);

	efree(ubuf);

	return rv;
}