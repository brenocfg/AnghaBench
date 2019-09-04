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
struct hdlc_proto {struct hdlc_proto* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct hdlc_proto* first_proto ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void unregister_hdlc_protocol(struct hdlc_proto *proto)
{
	struct hdlc_proto **p;

	rtnl_lock();
	p = &first_proto;
	while (*p != proto) {
		BUG_ON(!*p);
		p = &((*p)->next);
	}
	*p = proto->next;
	rtnl_unlock();
}