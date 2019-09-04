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
struct tty_struct {TYPE_1__* ops; } ;
struct r3964_info {struct tty_struct* tty; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_chars ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 

__attribute__((used)) static void flush(struct r3964_info *pInfo)
{
	struct tty_struct *tty = pInfo->tty;

	if (tty == NULL || tty->ops->flush_chars == NULL)
		return;
	tty->ops->flush_chars(tty);
}