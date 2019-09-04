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
struct tty_struct {struct syncppp* disc_data; } ;
struct syncppp {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  disc_data_lock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct syncppp *sp_get(struct tty_struct *tty)
{
	struct syncppp *ap;

	read_lock(&disc_data_lock);
	ap = tty->disc_data;
	if (ap != NULL)
		refcount_inc(&ap->refcnt);
	read_unlock(&disc_data_lock);
	return ap;
}