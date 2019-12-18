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
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__* HPDF_Number ;
typedef  int /*<<< orphan*/  HPDF_INT32 ;

/* Variables and functions */

void
HPDF_Number_SetValue  (HPDF_Number  obj,
                       HPDF_INT32   value)
{
    obj->value =value;
}