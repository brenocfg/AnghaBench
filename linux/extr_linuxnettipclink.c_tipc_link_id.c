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
typedef  int u32 ;
struct tipc_link {int peer_bearer_id; int bearer_id; } ;

/* Variables and functions */

u32 tipc_link_id(struct tipc_link *l)
{
	return l->peer_bearer_id << 16 | l->bearer_id;
}