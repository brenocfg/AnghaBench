#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* str; TYPE_1__* state; } ;
struct TYPE_4__ {int charlen; int posbyte; } ;
typedef  TYPE_2__ TParser ;

/* Variables and functions */

__attribute__((used)) static int
p_isurlchar(TParser *prs)
{
	char		ch;

	/* no non-ASCII need apply */
	if (prs->state->charlen != 1)
		return 0;
	ch = *(prs->str + prs->state->posbyte);
	/* no spaces or control characters */
	if (ch <= 0x20 || ch >= 0x7F)
		return 0;
	/* reject characters disallowed by RFC 3986 */
	switch (ch)
	{
		case '"':
		case '<':
		case '>':
		case '\\':
		case '^':
		case '`':
		case '{':
		case '|':
		case '}':
			return 0;
	}
	return 1;
}