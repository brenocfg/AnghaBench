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
struct udp_media_addr {int dummy; } ;
struct tipc_media_addr {int /*<<< orphan*/  broadcast; int /*<<< orphan*/  value; int /*<<< orphan*/  media_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_BROADCAST_SUPPORT ; 
 int /*<<< orphan*/  TIPC_MEDIA_TYPE_UDP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct udp_media_addr*,int) ; 
 int /*<<< orphan*/  memset (struct tipc_media_addr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tipc_udp_is_mcast_addr (struct udp_media_addr*) ; 

__attribute__((used)) static void tipc_udp_media_addr_set(struct tipc_media_addr *addr,
				    struct udp_media_addr *ua)
{
	memset(addr, 0, sizeof(struct tipc_media_addr));
	addr->media_id = TIPC_MEDIA_TYPE_UDP;
	memcpy(addr->value, ua, sizeof(struct udp_media_addr));

	if (tipc_udp_is_mcast_addr(ua))
		addr->broadcast = TIPC_BROADCAST_SUPPORT;
}