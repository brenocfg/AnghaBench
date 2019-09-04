#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct unix_sock {int /*<<< orphan*/  bindlock; int /*<<< orphan*/  addr; } ;
struct unix_address {size_t hash; scalar_t__ len; TYPE_1__* name; int /*<<< orphan*/  refcnt; } ;
struct socket {int /*<<< orphan*/  type; struct sock* sk; } ;
struct sock {size_t sk_type; } ;
struct net {int dummy; } ;
struct TYPE_3__ {scalar_t__ sun_path; int /*<<< orphan*/  sun_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __unix_find_socket_byname (struct net*,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  __unix_insert_socket (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  __unix_remove_socket (struct sock*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  csum_partial (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct unix_address*) ; 
 struct unix_address* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,struct unix_address*) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sprintf (scalar_t__,char*,int) ; 
 size_t unix_hash_fold (int /*<<< orphan*/ ) ; 
 struct unix_sock* unix_sk (struct sock*) ; 
 int /*<<< orphan*/ * unix_socket_table ; 
 int /*<<< orphan*/  unix_table_lock ; 

__attribute__((used)) static int unix_autobind(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct net *net = sock_net(sk);
	struct unix_sock *u = unix_sk(sk);
	static u32 ordernum = 1;
	struct unix_address *addr;
	int err;
	unsigned int retries = 0;

	err = mutex_lock_interruptible(&u->bindlock);
	if (err)
		return err;

	err = 0;
	if (u->addr)
		goto out;

	err = -ENOMEM;
	addr = kzalloc(sizeof(*addr) + sizeof(short) + 16, GFP_KERNEL);
	if (!addr)
		goto out;

	addr->name->sun_family = AF_UNIX;
	refcount_set(&addr->refcnt, 1);

retry:
	addr->len = sprintf(addr->name->sun_path+1, "%05x", ordernum) + 1 + sizeof(short);
	addr->hash = unix_hash_fold(csum_partial(addr->name, addr->len, 0));

	spin_lock(&unix_table_lock);
	ordernum = (ordernum+1)&0xFFFFF;

	if (__unix_find_socket_byname(net, addr->name, addr->len, sock->type,
				      addr->hash)) {
		spin_unlock(&unix_table_lock);
		/*
		 * __unix_find_socket_byname() may take long time if many names
		 * are already in use.
		 */
		cond_resched();
		/* Give up if all names seems to be in use. */
		if (retries++ == 0xFFFFF) {
			err = -ENOSPC;
			kfree(addr);
			goto out;
		}
		goto retry;
	}
	addr->hash ^= sk->sk_type;

	__unix_remove_socket(sk);
	smp_store_release(&u->addr, addr);
	__unix_insert_socket(&unix_socket_table[addr->hash], sk);
	spin_unlock(&unix_table_lock);
	err = 0;

out:	mutex_unlock(&u->bindlock);
	return err;
}