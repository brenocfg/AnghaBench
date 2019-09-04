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
struct tty_struct {struct n_tty_data* disc_data; } ;
struct n_tty_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ I_IGNPAR (struct tty_struct*) ; 
 scalar_t__ I_INPCK (struct tty_struct*) ; 
 scalar_t__ I_PARMRK (struct tty_struct*) ; 
 int /*<<< orphan*/  put_tty_queue (unsigned char,struct n_tty_data*) ; 

__attribute__((used)) static void n_tty_receive_parity_error(struct tty_struct *tty, unsigned char c)
{
	struct n_tty_data *ldata = tty->disc_data;

	if (I_INPCK(tty)) {
		if (I_IGNPAR(tty))
			return;
		if (I_PARMRK(tty)) {
			put_tty_queue('\377', ldata);
			put_tty_queue('\0', ldata);
			put_tty_queue(c, ldata);
		} else
			put_tty_queue('\0', ldata);
	} else
		put_tty_queue(c, ldata);
}