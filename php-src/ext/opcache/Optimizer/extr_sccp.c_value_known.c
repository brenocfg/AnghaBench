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
typedef  int zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  IS_BOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_TOP (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline zend_bool value_known(zval *zv) {
	return !IS_TOP(zv) && !IS_BOT(zv);
}