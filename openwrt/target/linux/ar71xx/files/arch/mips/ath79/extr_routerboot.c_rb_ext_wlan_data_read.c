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
struct file {int dummy; } ;
struct bin_attribute {size_t size; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;

/* Variables and functions */
 size_t EFBIG ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * rb_ext_wlan_data ; 

__attribute__((used)) static ssize_t
rb_ext_wlan_data_read(struct file *filp, struct kobject *kobj,
		      struct bin_attribute *attr, char *buf,
		      loff_t off, size_t count)
{
         if (off + count > attr->size)
                 return -EFBIG;

         memcpy(buf, &rb_ext_wlan_data[off], count);

         return count;
}