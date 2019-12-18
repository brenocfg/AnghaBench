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
struct file {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  file_alloc_security ; 
 int lsm_file_alloc (struct file*) ; 
 int /*<<< orphan*/  security_file_free (struct file*) ; 
 scalar_t__ unlikely (int) ; 

int security_file_alloc(struct file *file)
{
	int rc = lsm_file_alloc(file);

	if (rc)
		return rc;
	rc = call_int_hook(file_alloc_security, 0, file);
	if (unlikely(rc))
		security_file_free(file);
	return rc;
}