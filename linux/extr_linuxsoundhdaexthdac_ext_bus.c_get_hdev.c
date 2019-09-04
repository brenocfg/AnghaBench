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
struct hdac_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct hdac_device* dev_to_hdac_dev (struct device*) ; 

__attribute__((used)) static inline struct hdac_device *get_hdev(struct device *dev)
{
	struct hdac_device *hdev = dev_to_hdac_dev(dev);
	return hdev;
}