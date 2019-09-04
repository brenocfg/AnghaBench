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
typedef  int /*<<< orphan*/  unchar ;
struct tty_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write_char ) (int /*<<< orphan*/  const) ;} ;

/* Variables and functions */
 TYPE_1__* dbg_io_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static int kgdb_nmi_tty_write(struct tty_struct *tty, const unchar *buf, int c)
{
	int i;

	for (i = 0; i < c; i++)
		dbg_io_ops->write_char(buf[i]);
	return c;
}