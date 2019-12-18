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
typedef  int /*<<< orphan*/  mysqli_object ;
typedef  int /*<<< orphan*/  MyG ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  Z_LVAL_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int driver_report_write(mysqli_object *obj, zval *value)
{
	MyG(report_mode) = Z_LVAL_P(value);
	/*FIXME*/
	/* zend_replace_error_handling(MyG(report_mode) & MYSQLI_REPORT_STRICT ? EH_THROW : EH_NORMAL, NULL, NULL); */
	return SUCCESS;
}