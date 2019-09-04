#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct x25_asy {scalar_t__ magic; int /*<<< orphan*/ * tty; TYPE_1__* dev; } ;
struct tty_struct {struct x25_asy* disc_data; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 int LAPB_OK ; 
 scalar_t__ X25_ASY_MAGIC ; 
 int /*<<< orphan*/  dev_close (TYPE_1__*) ; 
 int lapb_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  x25_asy_free (struct x25_asy*) ; 

__attribute__((used)) static void x25_asy_close_tty(struct tty_struct *tty)
{
	struct x25_asy *sl = tty->disc_data;
	int err;

	/* First make sure we're connected. */
	if (!sl || sl->magic != X25_ASY_MAGIC)
		return;

	rtnl_lock();
	if (sl->dev->flags & IFF_UP)
		dev_close(sl->dev);
	rtnl_unlock();

	err = lapb_unregister(sl->dev);
	if (err != LAPB_OK)
		pr_err("x25_asy_close: lapb_unregister error: %d\n",
		       err);

	tty->disc_data = NULL;
	sl->tty = NULL;
	x25_asy_free(sl);
}