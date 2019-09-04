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
struct padata_instance {int dummy; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __padata_free (struct padata_instance*) ; 
 struct padata_instance* kobj2pinst (struct kobject*) ; 

__attribute__((used)) static void padata_sysfs_release(struct kobject *kobj)
{
	struct padata_instance *pinst = kobj2pinst(kobj);
	__padata_free(pinst);
}