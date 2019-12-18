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
struct class_dev_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  class_dev_iter_exit (struct class_dev_iter*) ; 

__attribute__((used)) static inline void nfc_device_iter_exit(struct class_dev_iter *iter)
{
	class_dev_iter_exit(iter);
}