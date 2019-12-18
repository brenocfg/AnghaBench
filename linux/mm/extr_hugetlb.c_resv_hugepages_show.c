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
struct hstate {int /*<<< orphan*/  resv_huge_pages; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct hstate* kobj_to_hstate (struct kobject*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t resv_hugepages_show(struct kobject *kobj,
					struct kobj_attribute *attr, char *buf)
{
	struct hstate *h = kobj_to_hstate(kobj, NULL);
	return sprintf(buf, "%lu\n", h->resv_huge_pages);
}