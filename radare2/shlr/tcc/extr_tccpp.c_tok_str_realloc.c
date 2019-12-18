#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int allocated_len; int* str; } ;
typedef  TYPE_1__ TokenString ;

/* Variables and functions */
 int* realloc (int*,int) ; 

__attribute__((used)) static int *tok_str_realloc(TokenString *s)
{
	int *str, len;

	if (s->allocated_len == 0) {
		len = 8;
	} else {
		len = s->allocated_len * 2;
	}
	str = realloc (s->str, len * sizeof(int));
	s->allocated_len = len;
	s->str = str;
	return str;
}