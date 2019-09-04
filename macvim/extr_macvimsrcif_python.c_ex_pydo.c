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
typedef  int /*<<< orphan*/  runner ;
typedef  int /*<<< orphan*/  rangeinitializer ;
struct TYPE_3__ {scalar_t__ arg; } ;
typedef  TYPE_1__ exarg_T ;

/* Variables and functions */
 int /*<<< orphan*/  DoPyCommand (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ init_range_cmd ; 
 scalar_t__ run_do ; 

void
ex_pydo(exarg_T *eap)
{
    DoPyCommand((char *)eap->arg,
	    (rangeinitializer) init_range_cmd,
	    (runner)run_do,
	    (void *)eap);
}