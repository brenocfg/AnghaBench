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
struct datalink_proto {int /*<<< orphan*/  request; scalar_t__ header_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct datalink_proto* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p8023_request ; 

struct datalink_proto *make_8023_client(void)
{
	struct datalink_proto *proto = kmalloc(sizeof(*proto), GFP_ATOMIC);

	if (proto) {
		proto->header_length = 0;
		proto->request	     = p8023_request;
	}
	return proto;
}