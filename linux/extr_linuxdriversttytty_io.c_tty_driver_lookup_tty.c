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
struct tty_struct {int dummy; } ;
struct tty_driver {struct tty_struct** ttys; TYPE_1__* ops; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct tty_struct* (* lookup ) (struct tty_driver*,struct file*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct tty_struct* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct tty_struct*) ; 
 struct tty_struct* stub1 (struct tty_driver*,struct file*,int) ; 
 int /*<<< orphan*/  tty_kref_get (struct tty_struct*) ; 

__attribute__((used)) static struct tty_struct *tty_driver_lookup_tty(struct tty_driver *driver,
		struct file *file, int idx)
{
	struct tty_struct *tty;

	if (driver->ops->lookup)
		if (!file)
			tty = ERR_PTR(-EIO);
		else
			tty = driver->ops->lookup(driver, file, idx);
	else
		tty = driver->ttys[idx];

	if (!IS_ERR(tty))
		tty_kref_get(tty);
	return tty;
}