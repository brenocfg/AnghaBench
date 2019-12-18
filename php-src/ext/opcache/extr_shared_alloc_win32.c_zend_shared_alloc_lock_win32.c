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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEL_LOG_ERROR ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ WAIT_FAILED ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_mutex ; 
 int /*<<< orphan*/  zend_accel_error (int /*<<< orphan*/ ,char*) ; 

void zend_shared_alloc_lock_win32(void)
{
	DWORD waitRes = WaitForSingleObject(memory_mutex, INFINITE);

	if (waitRes == WAIT_FAILED) {
		zend_accel_error(ACCEL_LOG_ERROR, "Cannot lock mutex");
	}
}