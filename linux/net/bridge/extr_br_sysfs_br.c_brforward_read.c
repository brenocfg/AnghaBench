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
struct net_bridge {int dummy; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
struct bin_attribute {int dummy; } ;
struct __fdb_entry {int dummy; } ;
typedef  int ssize_t ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int br_fdb_fillbuf (struct net_bridge*,char*,size_t,int) ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 struct net_bridge* to_bridge (struct device*) ; 

__attribute__((used)) static ssize_t brforward_read(struct file *filp, struct kobject *kobj,
			      struct bin_attribute *bin_attr,
			      char *buf, loff_t off, size_t count)
{
	struct device *dev = kobj_to_dev(kobj);
	struct net_bridge *br = to_bridge(dev);
	int n;

	/* must read whole records */
	if (off % sizeof(struct __fdb_entry) != 0)
		return -EINVAL;

	n =  br_fdb_fillbuf(br, buf,
			    count / sizeof(struct __fdb_entry),
			    off / sizeof(struct __fdb_entry));

	if (n > 0)
		n *= sizeof(struct __fdb_entry);

	return n;
}