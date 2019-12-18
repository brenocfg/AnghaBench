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
typedef  int /*<<< orphan*/  TokenSym ;

/* Variables and functions */
 int CH_EOF ; 
 int TOK_HASH_SIZE ; 
 int /*<<< orphan*/  TOK_IDENT ; 
 int /*<<< orphan*/  hash_ident ; 
 scalar_t__ isid (int) ; 
 int* isidnum_table ; 
 scalar_t__ isnum (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * table_ident ; 
 char* tcc_keywords ; 
 int /*<<< orphan*/  tok_alloc (char const*,int) ; 
 int /*<<< orphan*/  tok_ident ; 

void preprocess_new(void)
{
	int i, c;
	const char *p, *r;

	/* init isid table */
	for (i = CH_EOF; i < 256; i++) {
		isidnum_table[i - CH_EOF] = isid (i) || isnum (i);
	}

	/* add all tokens */
	table_ident = NULL;
	memset (hash_ident, 0, TOK_HASH_SIZE * sizeof(TokenSym *));

	tok_ident = TOK_IDENT;
	p = tcc_keywords;
	while (*p) {
		r = p;
		for (;;) {
			c = *r++;
			if (c == '\0') {
				break;
			}
		}
		tok_alloc (p, r - p - 1);
		p = r;
	}
}