#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * digits; int /*<<< orphan*/  sign; int /*<<< orphan*/  dscale; int /*<<< orphan*/  rscale; int /*<<< orphan*/  weight; } ;
typedef  TYPE_1__ numeric ;
struct TYPE_8__ {int ndigits; int /*<<< orphan*/ * digits; int /*<<< orphan*/  sign; int /*<<< orphan*/  dscale; int /*<<< orphan*/  rscale; int /*<<< orphan*/  weight; } ;
typedef  TYPE_2__ decimal ;

/* Variables and functions */
 scalar_t__ alloc_var (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zero_var (TYPE_1__*) ; 

int
PGTYPESnumeric_from_decimal(decimal *src, numeric *dst)
{
	int			i;

	zero_var(dst);

	dst->weight = src->weight;
	dst->rscale = src->rscale;
	dst->dscale = src->dscale;
	dst->sign = src->sign;

	if (alloc_var(dst, src->ndigits) != 0)
		return -1;

	for (i = 0; i < src->ndigits; i++)
		dst->digits[i] = src->digits[i];

	return 0;
}