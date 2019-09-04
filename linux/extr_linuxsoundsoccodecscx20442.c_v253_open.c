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
struct tty_struct {int receive_room; int /*<<< orphan*/ * disc_data; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* write ) (struct tty_struct*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int stub1 (struct tty_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v253_init ; 

__attribute__((used)) static int v253_open(struct tty_struct *tty)
{
	int ret, len = strlen(v253_init);

	/* Doesn't make sense without write callback */
	if (!tty->ops->write)
		return -EINVAL;

	/* Won't work if no codec pointer has been passed by a card driver */
	if (!tty->disc_data)
		return -ENODEV;

	tty->receive_room = 16;
	if (tty->ops->write(tty, v253_init, len) != len) {
		ret = -EIO;
		goto err;
	}
	/* Actual setup will be performed after the modem responds. */
	return 0;
err:
	tty->disc_data = NULL;
	return ret;
}