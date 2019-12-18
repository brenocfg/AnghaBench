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
struct token {size_t size; int /*<<< orphan*/  content; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int directive_compare(const void *_key, const void *_pdir)
{
	const struct token *token = _key;
	const char *const *pdir = _pdir, *dir = *pdir;
	size_t dlen, clen;
	int val;

	dlen = strlen(dir);
	clen = (dlen < token->size) ? dlen : token->size;

	//debug("cmp(%s,%s) = ", token->content, dir);

	val = memcmp(token->content, dir, clen);
	if (val != 0) {
		//debug("%d [cmp]\n", val);
		return val;
	}

	if (dlen == token->size) {
		//debug("0\n");
		return 0;
	}
	//debug("%d\n", (int)dlen - (int)token->size);
	return dlen - token->size; /* shorter -> negative */
}