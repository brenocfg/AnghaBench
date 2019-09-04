#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/ * disc_data; } ;
struct TYPE_2__ {int (* open ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/ * cx20442_codec ; 
 int stub1 (struct tty_struct*) ; 
 TYPE_1__ v253_ops ; 

__attribute__((used)) static int cx81801_open(struct tty_struct *tty)
{
	int ret;

	if (!cx20442_codec)
		return -ENODEV;

	/*
	 * Pass the codec structure pointer for use by other ldisc callbacks,
	 * both the card and the codec specific parts.
	 */
	tty->disc_data = cx20442_codec;

	ret = v253_ops.open(tty);

	if (ret < 0)
		tty->disc_data = NULL;

	return ret;
}