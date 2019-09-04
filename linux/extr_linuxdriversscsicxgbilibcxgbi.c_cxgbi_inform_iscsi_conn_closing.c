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
struct cxgbi_sock {scalar_t__ state; int /*<<< orphan*/  callback_lock; scalar_t__ user_data; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ CTP_ESTABLISHED ; 
 int CXGBI_DBG_SOCK ; 
 int /*<<< orphan*/  ISCSI_ERR_TCP_CONN_CLOSE ; 
 int /*<<< orphan*/  iscsi_conn_failure (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cxgbi_inform_iscsi_conn_closing(struct cxgbi_sock *csk)
{
	log_debug(1 << CXGBI_DBG_SOCK,
		"csk 0x%p, state %u, flags 0x%lx, conn 0x%p.\n",
		csk, csk->state, csk->flags, csk->user_data);

	if (csk->state != CTP_ESTABLISHED) {
		read_lock_bh(&csk->callback_lock);
		if (csk->user_data)
			iscsi_conn_failure(csk->user_data,
					ISCSI_ERR_TCP_CONN_CLOSE);
		read_unlock_bh(&csk->callback_lock);
	}
}