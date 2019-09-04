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
struct php_user_filter_data {int /*<<< orphan*/  classname; } ;

/* Variables and functions */
 struct php_user_filter_data* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (struct php_user_filter_data*) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filter_item_dtor(zval *zv)
{
	struct php_user_filter_data *fdat = Z_PTR_P(zv);
	zend_string_release_ex(fdat->classname, 0);
	efree(fdat);
}