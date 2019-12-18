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
struct TYPE_3__ {scalar_t__ value; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_Real ;
typedef  scalar_t__ HPDF_REAL ;

/* Variables and functions */
 scalar_t__ HPDF_LIMIT_MAX_REAL ; 
 scalar_t__ HPDF_LIMIT_MIN_REAL ; 
 int /*<<< orphan*/  HPDF_OK ; 
 int /*<<< orphan*/  HPDF_REAL_OUT_OF_RANGE ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_Real_SetValue  (HPDF_Real  obj,
                     HPDF_REAL  value)
{
    HPDF_STATUS ret = HPDF_OK;

    if (value > HPDF_LIMIT_MAX_REAL)
        return HPDF_SetError (obj->error, HPDF_REAL_OUT_OF_RANGE, 0);

    if (value < HPDF_LIMIT_MIN_REAL)
        return HPDF_SetError (obj->error, HPDF_REAL_OUT_OF_RANGE, 0);

    obj->value =value;

    return ret;
}