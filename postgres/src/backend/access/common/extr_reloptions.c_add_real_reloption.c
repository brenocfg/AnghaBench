#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double default_val; double min; double max; } ;
typedef  TYPE_1__ relopt_real ;
typedef  int /*<<< orphan*/  relopt_gen ;
typedef  int /*<<< orphan*/  bits32 ;
typedef  int /*<<< orphan*/  LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  RELOPT_TYPE_REAL ; 
 int /*<<< orphan*/  add_reloption (int /*<<< orphan*/ *) ; 
 scalar_t__ allocate_reloption (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 

void
add_real_reloption(bits32 kinds, const char *name, const char *desc, double default_val,
				   double min_val, double max_val, LOCKMODE lockmode)
{
	relopt_real *newoption;

	newoption = (relopt_real *) allocate_reloption(kinds, RELOPT_TYPE_REAL,
												   name, desc, lockmode);
	newoption->default_val = default_val;
	newoption->min = min_val;
	newoption->max = max_val;

	add_reloption((relopt_gen *) newoption);
}