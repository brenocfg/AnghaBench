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
struct tty_struct {struct tty_ldisc* ldisc; } ;
struct tty_ldisc {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_buffer ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  TCIFLUSH 130 
#define  TCIOFLUSH 129 
#define  TCOFLUSH 128 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  stub2 (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_unthrottle (struct tty_struct*) ; 

__attribute__((used)) static int __tty_perform_flush(struct tty_struct *tty, unsigned long arg)
{
	struct tty_ldisc *ld = tty->ldisc;

	switch (arg) {
	case TCIFLUSH:
		if (ld && ld->ops->flush_buffer) {
			ld->ops->flush_buffer(tty);
			tty_unthrottle(tty);
		}
		break;
	case TCIOFLUSH:
		if (ld && ld->ops->flush_buffer) {
			ld->ops->flush_buffer(tty);
			tty_unthrottle(tty);
		}
		/* fall through */
	case TCOFLUSH:
		tty_driver_flush_buffer(tty);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}