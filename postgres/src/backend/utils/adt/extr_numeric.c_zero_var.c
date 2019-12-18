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
struct TYPE_3__ {int /*<<< orphan*/  sign; scalar_t__ weight; scalar_t__ ndigits; int /*<<< orphan*/ * digits; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ NumericVar ;

/* Variables and functions */
 int /*<<< orphan*/  NUMERIC_POS ; 
 int /*<<< orphan*/  digitbuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zero_var(NumericVar *var)
{
	digitbuf_free(var->buf);
	var->buf = NULL;
	var->digits = NULL;
	var->ndigits = 0;
	var->weight = 0;			/* by convention; doesn't really matter */
	var->sign = NUMERIC_POS;	/* anything but NAN... */
}