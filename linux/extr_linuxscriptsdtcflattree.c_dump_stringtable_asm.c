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
struct data {char* val; int len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void dump_stringtable_asm(FILE *f, struct data strbuf)
{
	const char *p;
	int len;

	p = strbuf.val;

	while (p < (strbuf.val + strbuf.len)) {
		len = strlen(p);
		fprintf(f, "\t.string \"%s\"\n", p);
		p += len+1;
	}
}