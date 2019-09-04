#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_5__ {int /*<<< orphan*/  is_nan; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _isnan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asin (int /*<<< orphan*/ ) ; 
 TYPE_3__ calc ; 
 int /*<<< orphan*/  validate_rad2angle (int /*<<< orphan*/ ) ; 

void rpn_asin(calc_number_t *c)
{
    c->f = validate_rad2angle(asin(c->f));
    if (_isnan(c->f))
        calc.is_nan = TRUE;
}