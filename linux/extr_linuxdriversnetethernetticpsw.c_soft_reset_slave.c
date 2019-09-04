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
struct cpsw_slave {int slave_num; TYPE_1__* sliver; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_2__ {int /*<<< orphan*/  soft_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  soft_reset (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void soft_reset_slave(struct cpsw_slave *slave)
{
	char name[32];

	snprintf(name, sizeof(name), "slave-%d", slave->slave_num);
	soft_reset(name, &slave->sliver->soft_reset);
}