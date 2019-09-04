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

/* Variables and functions */
 int /*<<< orphan*/  ACCEL_LOG_FATAL ; 
 int /*<<< orphan*/  ACCEL_MUTEX_NAME ; 
 int /*<<< orphan*/  CreateMutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_name_with_username (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_mutex ; 
 int /*<<< orphan*/  zend_accel_error (int /*<<< orphan*/ ,char*) ; 

void zend_shared_alloc_create_lock(void)
{
	memory_mutex = CreateMutex(NULL, FALSE, create_name_with_username(ACCEL_MUTEX_NAME));
	if (!memory_mutex) {
		zend_accel_error(ACCEL_LOG_FATAL, "Cannot create mutex");
		return;
	}
	ReleaseMutex(memory_mutex);
}