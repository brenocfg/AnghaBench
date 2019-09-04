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
struct tty_struct {struct mkiss* disc_data; } ;
struct mkiss {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disc_data_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mkiss *mkiss_get(struct tty_struct *tty)
{
	struct mkiss *ax;

	read_lock(&disc_data_lock);
	ax = tty->disc_data;
	if (ax)
		atomic_inc(&ax->refcnt);
	read_unlock(&disc_data_lock);

	return ax;
}