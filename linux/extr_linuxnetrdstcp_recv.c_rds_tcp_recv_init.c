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
struct rds_tcp_incoming {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_tcp_incoming_slab ; 

int rds_tcp_recv_init(void)
{
	rds_tcp_incoming_slab = kmem_cache_create("rds_tcp_incoming",
					sizeof(struct rds_tcp_incoming),
					0, 0, NULL);
	if (!rds_tcp_incoming_slab)
		return -ENOMEM;
	return 0;
}