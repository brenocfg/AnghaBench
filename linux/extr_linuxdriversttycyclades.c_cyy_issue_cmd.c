#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  base_addr; } ;
struct TYPE_5__ {TYPE_1__ cyy; } ;
struct cyclades_port {TYPE_3__* card; TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  bus_index; } ;

/* Variables and functions */
 int __cyy_issue_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cyy_issue_cmd(struct cyclades_port *port, u8 cmd)
{
	return __cyy_issue_cmd(port->u.cyy.base_addr, cmd,
			port->card->bus_index);
}