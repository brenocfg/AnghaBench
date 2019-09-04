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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_expedited ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t rcu_expedited_show(struct kobject *kobj,
				  struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", READ_ONCE(rcu_expedited));
}