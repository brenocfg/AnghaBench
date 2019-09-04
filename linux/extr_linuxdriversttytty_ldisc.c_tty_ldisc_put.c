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
struct tty_ldisc {int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  kfree (struct tty_ldisc*) ; 
 int /*<<< orphan*/  put_ldops (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tty_ldisc_put(struct tty_ldisc *ld)
{
	if (WARN_ON_ONCE(!ld))
		return;

	put_ldops(ld->ops);
	kfree(ld);
}