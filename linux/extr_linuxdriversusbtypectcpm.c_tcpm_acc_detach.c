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
struct tcpm_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcpm_detach (struct tcpm_port*) ; 

__attribute__((used)) static void tcpm_acc_detach(struct tcpm_port *port)
{
	tcpm_detach(port);
}