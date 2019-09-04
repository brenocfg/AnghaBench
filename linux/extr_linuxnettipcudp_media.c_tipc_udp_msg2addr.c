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
struct tipc_media_addr {int dummy; } ;
struct tipc_bearer {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int TIPC_MEDIA_ADDR_OFFSET ; 
 size_t TIPC_MEDIA_TYPE_OFFSET ; 
 char TIPC_MEDIA_TYPE_UDP ; 
 int /*<<< orphan*/  tipc_udp_media_addr_set (struct tipc_media_addr*,struct udp_media_addr*) ; 

__attribute__((used)) static int tipc_udp_msg2addr(struct tipc_bearer *b, struct tipc_media_addr *a,
			     char *msg)
{
	struct udp_media_addr *ua;

	ua = (struct udp_media_addr *) (msg + TIPC_MEDIA_ADDR_OFFSET);
	if (msg[TIPC_MEDIA_TYPE_OFFSET] != TIPC_MEDIA_TYPE_UDP)
		return -EINVAL;
	tipc_udp_media_addr_set(a, ua);
	return 0;
}