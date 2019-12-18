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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtoull (char const*,int /*<<< orphan*/ ,unsigned long long*) ; 
 unsigned long long swsusp_resume_block ; 

__attribute__((used)) static ssize_t resume_offset_store(struct kobject *kobj,
				   struct kobj_attribute *attr, const char *buf,
				   size_t n)
{
	unsigned long long offset;
	int rc;

	rc = kstrtoull(buf, 0, &offset);
	if (rc)
		return rc;
	swsusp_resume_block = offset;

	return n;
}