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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_accel_error (int /*<<< orphan*/ ,char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void no_memory_bailout(size_t allocate_size, char *error)
{
	zend_accel_error(ACCEL_LOG_FATAL, "Unable to allocate shared memory segment of %zu bytes: %s: %s (%d)", allocate_size, error?error:"unknown", strerror(errno), errno );
}