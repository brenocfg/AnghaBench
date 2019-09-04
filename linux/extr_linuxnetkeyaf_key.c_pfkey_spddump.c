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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sadb_msg {int /*<<< orphan*/  sadb_msg_pid; int /*<<< orphan*/  sadb_msg_version; } ;
struct TYPE_3__ {int /*<<< orphan*/  policy; } ;
struct TYPE_4__ {TYPE_1__ u; int /*<<< orphan*/  done; int /*<<< orphan*/ * dump; int /*<<< orphan*/  msg_portid; int /*<<< orphan*/  msg_version; } ;
struct pfkey_sock {int /*<<< orphan*/  dump_lock; TYPE_2__ dump; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  XFRM_POLICY_TYPE_MAIN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pfkey_do_dump (struct pfkey_sock*) ; 
 int /*<<< orphan*/ * pfkey_dump_sp ; 
 int /*<<< orphan*/  pfkey_dump_sp_done ; 
 struct pfkey_sock* pfkey_sk (struct sock*) ; 
 int /*<<< orphan*/  xfrm_policy_walk_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pfkey_spddump(struct sock *sk, struct sk_buff *skb, const struct sadb_msg *hdr, void * const *ext_hdrs)
{
	struct pfkey_sock *pfk = pfkey_sk(sk);

	mutex_lock(&pfk->dump_lock);
	if (pfk->dump.dump != NULL) {
		mutex_unlock(&pfk->dump_lock);
		return -EBUSY;
	}

	pfk->dump.msg_version = hdr->sadb_msg_version;
	pfk->dump.msg_portid = hdr->sadb_msg_pid;
	pfk->dump.dump = pfkey_dump_sp;
	pfk->dump.done = pfkey_dump_sp_done;
	xfrm_policy_walk_init(&pfk->dump.u.policy, XFRM_POLICY_TYPE_MAIN);
	mutex_unlock(&pfk->dump_lock);

	return pfkey_do_dump(pfk);
}