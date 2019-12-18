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
struct at_msghdr {scalar_t__ msgtype; int datalen; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  ip_type4 ;

/* Variables and functions */
 int /*<<< orphan*/  ATD_CLIENT ; 
 int /*<<< orphan*/  ATD_SERVER ; 
 scalar_t__ ATM_GETNAME ; 
 int /*<<< orphan*/  MUTEX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ getmessage (int /*<<< orphan*/ ,struct at_msghdr*,char*) ; 
 int /*<<< orphan*/  internal_ips_lock ; 
 scalar_t__ sendmessage (int /*<<< orphan*/ ,struct at_msghdr*,int /*<<< orphan*/ *) ; 

size_t at_get_host_for_ip(ip_type4 ip, char* readbuf) {
	struct at_msghdr msg = {.msgtype = ATM_GETNAME, .datalen = sizeof(ip_type4) };
	size_t res = 0;
	MUTEX_LOCK(internal_ips_lock);
	if(sendmessage(ATD_SERVER, &msg, &ip) && getmessage(ATD_CLIENT, &msg, readbuf)) {
		if((ptrdiff_t) msg.datalen <= 0) res = 0;
		else res = msg.datalen - 1;
	}
	assert(msg.msgtype == ATM_GETNAME);
	MUTEX_UNLOCK(internal_ips_lock);
	return res;
}