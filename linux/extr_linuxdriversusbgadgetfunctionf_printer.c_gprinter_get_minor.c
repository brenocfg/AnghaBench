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

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PRINTER_MINORS ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printer_ida ; 

__attribute__((used)) static inline int gprinter_get_minor(void)
{
	int ret;

	ret = ida_simple_get(&printer_ida, 0, 0, GFP_KERNEL);
	if (ret >= PRINTER_MINORS) {
		ida_simple_remove(&printer_ida, ret);
		ret = -ENODEV;
	}

	return ret;
}