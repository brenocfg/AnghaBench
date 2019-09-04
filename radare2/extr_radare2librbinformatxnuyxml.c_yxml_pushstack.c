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
struct TYPE_3__ {int stacklen; int stacksize; unsigned int* stack; } ;
typedef  TYPE_1__ yxml_t ;
typedef  int /*<<< orphan*/  yxml_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  YXML_ESTACK ; 
 int /*<<< orphan*/  YXML_OK ; 

__attribute__((used)) static yxml_ret_t yxml_pushstack(yxml_t *x, char **res, unsigned ch) {
	if(x->stacklen+2 >= x->stacksize)
		return YXML_ESTACK;
	x->stacklen++;
	*res = (char *)x->stack+x->stacklen;
	x->stack[x->stacklen] = ch;
	x->stacklen++;
	x->stack[x->stacklen] = 0;
	return YXML_OK;
}