#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  port; int /*<<< orphan*/  termios_rwsem; TYPE_2__* ops; struct tty_ldisc* ldisc; int /*<<< orphan*/  flags; } ;
struct tty_ldisc {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_ldisc ) (struct tty_struct*) ;} ;
struct TYPE_3__ {int num; } ;

/* Variables and functions */
 int EIO ; 
 int HZ ; 
 scalar_t__ IS_ERR (struct tty_ldisc*) ; 
 int PTR_ERR (struct tty_ldisc*) ; 
 int /*<<< orphan*/  TTY_HUPPED ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_buffer_restart_work (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_ldisc_close (struct tty_struct*,struct tty_ldisc*) ; 
 struct tty_ldisc* tty_ldisc_get (struct tty_struct*,int) ; 
 int tty_ldisc_lock (struct tty_struct*,int) ; 
 int tty_ldisc_open (struct tty_struct*,struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_put (struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_restore (struct tty_struct*,struct tty_ldisc*) ; 
 int /*<<< orphan*/  tty_ldisc_unlock (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_lock (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_set_termios_ldisc (struct tty_struct*,int) ; 
 int /*<<< orphan*/  tty_unlock (struct tty_struct*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int tty_set_ldisc(struct tty_struct *tty, int disc)
{
	int retval;
	struct tty_ldisc *old_ldisc, *new_ldisc;

	new_ldisc = tty_ldisc_get(tty, disc);
	if (IS_ERR(new_ldisc))
		return PTR_ERR(new_ldisc);

	tty_lock(tty);
	retval = tty_ldisc_lock(tty, 5 * HZ);
	if (retval)
		goto err;

	if (!tty->ldisc) {
		retval = -EIO;
		goto out;
	}

	/* Check the no-op case */
	if (tty->ldisc->ops->num == disc)
		goto out;

	if (test_bit(TTY_HUPPED, &tty->flags)) {
		/* We were raced by hangup */
		retval = -EIO;
		goto out;
	}

	old_ldisc = tty->ldisc;

	/* Shutdown the old discipline. */
	tty_ldisc_close(tty, old_ldisc);

	/* Now set up the new line discipline. */
	tty->ldisc = new_ldisc;
	tty_set_termios_ldisc(tty, disc);

	retval = tty_ldisc_open(tty, new_ldisc);
	if (retval < 0) {
		/* Back to the old one or N_TTY if we can't */
		tty_ldisc_put(new_ldisc);
		tty_ldisc_restore(tty, old_ldisc);
	}

	if (tty->ldisc->ops->num != old_ldisc->ops->num && tty->ops->set_ldisc) {
		down_read(&tty->termios_rwsem);
		tty->ops->set_ldisc(tty);
		up_read(&tty->termios_rwsem);
	}

	/* At this point we hold a reference to the new ldisc and a
	   reference to the old ldisc, or we hold two references to
	   the old ldisc (if it was restored as part of error cleanup
	   above). In either case, releasing a single reference from
	   the old ldisc is correct. */
	new_ldisc = old_ldisc;
out:
	tty_ldisc_unlock(tty);

	/* Restart the work queue in case no characters kick it off. Safe if
	   already running */
	tty_buffer_restart_work(tty->port);
err:
	tty_ldisc_put(new_ldisc);	/* drop the extra reference */
	tty_unlock(tty);
	return retval;
}