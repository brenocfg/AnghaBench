#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  timelib_tzinfo ;

/* Variables and functions */
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timelib_tzinfo_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _php_date_tzinfo_dtor(zval *zv) /* {{{ */
{
	timelib_tzinfo *tzi = (timelib_tzinfo*)Z_PTR_P(zv);

	timelib_tzinfo_dtor(tzi);
}