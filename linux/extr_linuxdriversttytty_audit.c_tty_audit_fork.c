#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct signal_struct {int /*<<< orphan*/  audit_tty; } ;
struct TYPE_4__ {TYPE_1__* signal; } ;
struct TYPE_3__ {int /*<<< orphan*/  audit_tty; } ;

/* Variables and functions */
 TYPE_2__* current ; 

void tty_audit_fork(struct signal_struct *sig)
{
	sig->audit_tty = current->signal->audit_tty;
}