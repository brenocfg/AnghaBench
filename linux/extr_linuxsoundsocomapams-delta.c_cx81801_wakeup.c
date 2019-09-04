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
struct TYPE_2__ {int /*<<< orphan*/  (* write_wakeup ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 TYPE_1__ v253_ops ; 

__attribute__((used)) static void cx81801_wakeup(struct tty_struct *tty)
{
	v253_ops.write_wakeup(tty);
}