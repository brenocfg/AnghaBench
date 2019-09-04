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
struct ceph_connection {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  con_flag_valid (unsigned long) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void con_flag_set(struct ceph_connection *con, unsigned long con_flag)
{
	BUG_ON(!con_flag_valid(con_flag));

	set_bit(con_flag, &con->flags);
}