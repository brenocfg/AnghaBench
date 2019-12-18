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
struct TYPE_3__ {int /*<<< orphan*/ * accuracy; } ;
typedef  TYPE_1__ TS_TST_INFO ;
typedef  int /*<<< orphan*/  TS_ACCURACY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * TS_ACCURACY_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_ACCURACY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TS_F_TS_TST_INFO_SET_ACCURACY ; 
 int /*<<< orphan*/  TSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int TS_TST_INFO_set_accuracy(TS_TST_INFO *a, TS_ACCURACY *accuracy)
{
    TS_ACCURACY *new_accuracy;

    if (a->accuracy == accuracy)
        return 1;
    new_accuracy = TS_ACCURACY_dup(accuracy);
    if (new_accuracy == NULL) {
        TSerr(TS_F_TS_TST_INFO_SET_ACCURACY, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    TS_ACCURACY_free(a->accuracy);
    a->accuracy = new_accuracy;
    return 1;
}