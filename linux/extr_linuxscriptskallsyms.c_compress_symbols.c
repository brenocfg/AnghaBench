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
struct TYPE_2__ {unsigned int len; unsigned char* sym; } ;

/* Variables and functions */
 unsigned char* find_token (unsigned char*,unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  forget_symbol (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  learn_symbol (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,unsigned int) ; 
 TYPE_1__* table ; 
 unsigned int table_cnt ; 

__attribute__((used)) static void compress_symbols(unsigned char *str, int idx)
{
	unsigned int i, len, size;
	unsigned char *p1, *p2;

	for (i = 0; i < table_cnt; i++) {

		len = table[i].len;
		p1 = table[i].sym;

		/* find the token on the symbol */
		p2 = find_token(p1, len, str);
		if (!p2) continue;

		/* decrease the counts for this symbol's tokens */
		forget_symbol(table[i].sym, len);

		size = len;

		do {
			*p2 = idx;
			p2++;
			size -= (p2 - p1);
			memmove(p2, p2 + 1, size);
			p1 = p2;
			len--;

			if (size < 2) break;

			/* find the token on the symbol */
			p2 = find_token(p1, size, str);

		} while (p2);

		table[i].len = len;

		/* increase the counts for this symbol's new tokens */
		learn_symbol(table[i].sym, len);
	}
}