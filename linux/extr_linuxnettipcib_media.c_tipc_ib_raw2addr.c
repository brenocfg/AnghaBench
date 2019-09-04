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
struct tipc_media_addr {int broadcast; int /*<<< orphan*/  media_id; int /*<<< orphan*/  value; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct tipc_bearer {TYPE_1__ bcast_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFINIBAND_ALEN ; 
 int /*<<< orphan*/  TIPC_MEDIA_TYPE_IB ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tipc_media_addr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tipc_ib_raw2addr(struct tipc_bearer *b,
			    struct tipc_media_addr *addr,
			    char *msg)
{
	memset(addr, 0, sizeof(*addr));
	memcpy(addr->value, msg, INFINIBAND_ALEN);
	addr->media_id = TIPC_MEDIA_TYPE_IB;
	addr->broadcast = !memcmp(msg, b->bcast_addr.value,
				  INFINIBAND_ALEN);
	return 0;
}