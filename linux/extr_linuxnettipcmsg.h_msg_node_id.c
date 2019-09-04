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
typedef  int /*<<< orphan*/  u8 ;
struct tipc_msg {int dummy; } ;

/* Variables and functions */
 scalar_t__ msg_data (struct tipc_msg*) ; 

__attribute__((used)) static inline u8 *msg_node_id(struct tipc_msg *hdr)
{
	return (u8 *)msg_data(hdr);
}