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
typedef  int /*<<< orphan*/  zend_long ;
typedef  int /*<<< orphan*/  EG ;

/* Variables and functions */
 int /*<<< orphan*/  zend_set_timeout_ex (int /*<<< orphan*/ ,int) ; 

void zend_set_timeout(zend_long seconds, int reset_signals) /* {{{ */
{

	EG(timeout_seconds) = seconds;
	zend_set_timeout_ex(seconds, reset_signals);
	EG(timed_out) = 0;
}