#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ndigits; int /*<<< orphan*/ * digits; int /*<<< orphan*/  sign; int /*<<< orphan*/  dscale; int /*<<< orphan*/  rscale; int /*<<< orphan*/  weight; } ;
typedef  TYPE_1__ numeric ;
struct TYPE_6__ {int ndigits; int /*<<< orphan*/ * digits; int /*<<< orphan*/  sign; int /*<<< orphan*/  dscale; int /*<<< orphan*/  rscale; int /*<<< orphan*/  weight; } ;
typedef  TYPE_2__ decimal ;

/* Variables and functions */
 int DECSIZE ; 
 int /*<<< orphan*/  PGTYPES_NUM_OVERFLOW ; 
 int /*<<< orphan*/  errno ; 

int
PGTYPESnumeric_to_decimal(numeric *src, decimal *dst)
{
	int			i;

	if (src->ndigits > DECSIZE)
	{
		errno = PGTYPES_NUM_OVERFLOW;
		return -1;
	}

	dst->weight = src->weight;
	dst->rscale = src->rscale;
	dst->dscale = src->dscale;
	dst->sign = src->sign;
	dst->ndigits = src->ndigits;

	for (i = 0; i < src->ndigits; i++)
		dst->digits[i] = src->digits[i];

	return 0;
}