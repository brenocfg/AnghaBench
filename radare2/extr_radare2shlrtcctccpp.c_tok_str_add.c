#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; int* str; int allocated_len; } ;
typedef  TYPE_1__ TokenString ;

/* Variables and functions */
 int* tok_str_realloc (TYPE_1__*) ; 

void tok_str_add(TokenString *s, int t)
{
	int len, *str;

	len = s->len;
	str = s->str;
	if (len >= s->allocated_len) {
		str = tok_str_realloc (s);
	}
	str[len++] = t;
	s->len = len;
}