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
typedef  int /*<<< orphan*/  u16 ;
struct nvme_fc_local_port {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
fcloop_create_queue(struct nvme_fc_local_port *localport,
			unsigned int qidx, u16 qsize,
			void **handle)
{
	*handle = localport;
	return 0;
}