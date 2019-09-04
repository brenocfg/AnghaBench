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
struct un_t {struct channel_t* un_ch; } ;
struct tty_struct {struct un_t* driver_data; } ;
struct dgnc_board {TYPE_1__* bd_ops; } ;
struct channel_t {struct dgnc_board* ch_bd; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* drain ) (struct tty_struct*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tty_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dgnc_tty_wait_until_sent(struct tty_struct *tty, int timeout)
{
	struct dgnc_board *bd;
	struct channel_t *ch;
	struct un_t *un;

	if (!tty)
		return;

	un = tty->driver_data;
	if (!un)
		return;

	ch = un->un_ch;
	if (!ch)
		return;

	bd = ch->ch_bd;
	if (!bd)
		return;

	bd->bd_ops->drain(tty, 0);
}