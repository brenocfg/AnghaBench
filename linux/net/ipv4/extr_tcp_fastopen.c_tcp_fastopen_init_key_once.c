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
typedef  int /*<<< orphan*/  u8 ;
struct tcp_fastopen_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcp_fastopen_ctx; } ;
struct net {TYPE_1__ ipv4; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int TCP_FASTOPEN_KEY_LENGTH ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 struct tcp_fastopen_context* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  tcp_fastopen_reset_cipher (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void tcp_fastopen_init_key_once(struct net *net)
{
	u8 key[TCP_FASTOPEN_KEY_LENGTH];
	struct tcp_fastopen_context *ctxt;

	rcu_read_lock();
	ctxt = rcu_dereference(net->ipv4.tcp_fastopen_ctx);
	if (ctxt) {
		rcu_read_unlock();
		return;
	}
	rcu_read_unlock();

	/* tcp_fastopen_reset_cipher publishes the new context
	 * atomically, so we allow this race happening here.
	 *
	 * All call sites of tcp_fastopen_cookie_gen also check
	 * for a valid cookie, so this is an acceptable risk.
	 */
	get_random_bytes(key, sizeof(key));
	tcp_fastopen_reset_cipher(net, NULL, key, NULL);
}