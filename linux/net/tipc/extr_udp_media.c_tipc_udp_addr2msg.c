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
struct tipc_media_addr {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int TIPC_MEDIA_ADDR_OFFSET ; 
 int /*<<< orphan*/  TIPC_MEDIA_INFO_SIZE ; 
 size_t TIPC_MEDIA_TYPE_OFFSET ; 
 char TIPC_MEDIA_TYPE_UDP ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tipc_udp_addr2msg(char *msg, struct tipc_media_addr *a)
{
	memset(msg, 0, TIPC_MEDIA_INFO_SIZE);
	msg[TIPC_MEDIA_TYPE_OFFSET] = TIPC_MEDIA_TYPE_UDP;
	memcpy(msg + TIPC_MEDIA_ADDR_OFFSET, a->value,
	       sizeof(struct udp_media_addr));
	return 0;
}