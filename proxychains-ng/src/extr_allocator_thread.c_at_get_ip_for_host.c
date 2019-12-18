#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct at_msghdr {scalar_t__ msgtype; size_t datalen; } ;
typedef  int /*<<< orphan*/  ip_type4 ;
struct TYPE_3__ {int /*<<< orphan*/  v4; } ;
struct TYPE_4__ {TYPE_1__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATD_CLIENT ; 
 int /*<<< orphan*/  ATD_SERVER ; 
 scalar_t__ ATM_GETIP ; 
 size_t MSG_LEN_MAX ; 
 int /*<<< orphan*/  MUTEX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ getmessage (int /*<<< orphan*/ ,struct at_msghdr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  internal_ips_lock ; 
 TYPE_2__ ip_type_invalid ; 
 scalar_t__ sendmessage (int /*<<< orphan*/ ,struct at_msghdr*,char*) ; 

ip_type4 at_get_ip_for_host(char* host, size_t len) {
	ip_type4 readbuf;
	MUTEX_LOCK(internal_ips_lock);
	if(len > MSG_LEN_MAX) goto inv;
	struct at_msghdr msg = {.msgtype = ATM_GETIP, .datalen = len + 1 };
	if(sendmessage(ATD_SERVER, &msg, host) &&
	   getmessage(ATD_CLIENT, &msg, &readbuf));
	else {
		inv:
		readbuf = ip_type_invalid.addr.v4;
	}
	assert(msg.msgtype == ATM_GETIP);
	MUTEX_UNLOCK(internal_ips_lock);
	return readbuf;
}