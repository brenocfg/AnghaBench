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
struct unix_address {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct sock {int dummy; } ;
struct msghdr {int /*<<< orphan*/  msg_name; int /*<<< orphan*/  msg_namelen; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct unix_address* smp_load_acquire (int /*<<< orphan*/ *) ; 
 TYPE_1__* unix_sk (struct sock*) ; 

__attribute__((used)) static void unix_copy_addr(struct msghdr *msg, struct sock *sk)
{
	struct unix_address *addr = smp_load_acquire(&unix_sk(sk)->addr);

	if (addr) {
		msg->msg_namelen = addr->len;
		memcpy(msg->msg_name, addr->name, addr->len);
	}
}