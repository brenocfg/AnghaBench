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
struct seq_file {struct renesas_usb3* private; } ;
struct renesas_usb3 {int /*<<< orphan*/  forced_b_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int renesas_usb3_b_device_show(struct seq_file *s, void *unused)
{
	struct renesas_usb3 *usb3 = s->private;

	seq_printf(s, "%d\n", usb3->forced_b_device);

	return 0;
}