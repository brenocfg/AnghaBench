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
struct sock {int /*<<< orphan*/  sk_allocation; } ;
struct iucv_sock {scalar_t__ msglimit; int /*<<< orphan*/  transport; int /*<<< orphan*/  src_user_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_IUCV_TRANS_IUCV ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_DMA ; 
 scalar_t__ IUCV_QUEUELEN_DEFAULT ; 
 int /*<<< orphan*/  __iucv_auto_name (struct iucv_sock*) ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 TYPE_1__ iucv_sk_list ; 
 int /*<<< orphan*/  iucv_userid ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_iucv ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iucv_sock_autobind(struct sock *sk)
{
	struct iucv_sock *iucv = iucv_sk(sk);
	int err = 0;

	if (unlikely(!pr_iucv))
		return -EPROTO;

	memcpy(iucv->src_user_id, iucv_userid, 8);
	iucv->transport = AF_IUCV_TRANS_IUCV;
	sk->sk_allocation |= GFP_DMA;

	write_lock_bh(&iucv_sk_list.lock);
	__iucv_auto_name(iucv);
	write_unlock_bh(&iucv_sk_list.lock);

	if (!iucv->msglimit)
		iucv->msglimit = IUCV_QUEUELEN_DEFAULT;

	return err;
}