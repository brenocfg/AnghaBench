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
struct nfc_dev {int dummy; } ;
struct device {int dummy; } ;
struct class_dev_iter {int dummy; } ;

/* Variables and functions */
 struct device* class_dev_iter_next (struct class_dev_iter*) ; 
 struct nfc_dev* to_nfc_dev (struct device*) ; 

__attribute__((used)) static inline struct nfc_dev *nfc_device_iter_next(struct class_dev_iter *iter)
{
	struct device *d = class_dev_iter_next(iter);
	if (!d)
		return NULL;

	return to_nfc_dev(d);
}