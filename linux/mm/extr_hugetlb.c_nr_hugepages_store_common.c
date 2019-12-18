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
struct hstate {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int __nr_hugepages_store_common (int,struct hstate*,int,unsigned long,size_t) ; 
 struct hstate* kobj_to_hstate (struct kobject*,int*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t nr_hugepages_store_common(bool obey_mempolicy,
					 struct kobject *kobj, const char *buf,
					 size_t len)
{
	struct hstate *h;
	unsigned long count;
	int nid;
	int err;

	err = kstrtoul(buf, 10, &count);
	if (err)
		return err;

	h = kobj_to_hstate(kobj, &nid);
	return __nr_hugepages_store_common(obey_mempolicy, h, nid, count, len);
}