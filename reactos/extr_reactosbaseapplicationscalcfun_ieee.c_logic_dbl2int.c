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
typedef  int /*<<< orphan*/  __int64 ;
struct TYPE_5__ {int /*<<< orphan*/  is_nan; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ calc ; 
 int /*<<< orphan*/  fabs (double) ; 
 scalar_t__ log10 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modf (int /*<<< orphan*/ ,double*) ; 

__int64 logic_dbl2int(calc_number_t *a)
{
    double   int_part;
    int      width;

    modf(a->f, &int_part);
    width = (int_part==0) ? 1 : (int)log10(fabs(int_part))+1;
    if (width > 63) {
        calc.is_nan = TRUE;
        return 0;
    }
    return (__int64)int_part;
}