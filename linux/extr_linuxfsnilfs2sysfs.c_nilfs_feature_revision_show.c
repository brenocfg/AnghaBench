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
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int NILFS_CURRENT_REV ; 
 int NILFS_MINOR_REV ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static ssize_t nilfs_feature_revision_show(struct kobject *kobj,
					    struct attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d.%d\n",
			NILFS_CURRENT_REV, NILFS_MINOR_REV);
}