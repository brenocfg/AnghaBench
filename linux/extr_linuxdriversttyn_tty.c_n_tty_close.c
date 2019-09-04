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
struct tty_struct {struct n_tty_data* disc_data; scalar_t__ link; } ;
struct n_tty_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  n_tty_packet_mode_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  vfree (struct n_tty_data*) ; 

__attribute__((used)) static void n_tty_close(struct tty_struct *tty)
{
	struct n_tty_data *ldata = tty->disc_data;

	if (tty->link)
		n_tty_packet_mode_flush(tty);

	vfree(ldata);
	tty->disc_data = NULL;
}