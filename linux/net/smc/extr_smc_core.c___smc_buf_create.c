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
struct TYPE_2__ {int sk_rcvbuf; int sk_sndbuf; } ;
struct smc_connection {int rmbe_size_short; int /*<<< orphan*/  sndbuf_space; struct smc_buf_desc* sndbuf_desc; int /*<<< orphan*/  rmbe_update_limit; int /*<<< orphan*/  bytes_to_rcv; struct smc_buf_desc* rmb_desc; struct smc_link_group* lgr; } ;
struct smc_sock {TYPE_1__ sk; struct smc_connection conn; } ;
struct smc_link_group {struct list_head* sndbufs; int /*<<< orphan*/  sndbufs_lock; struct list_head* rmbs; int /*<<< orphan*/  rmbs_lock; } ;
struct smc_buf_desc {int used; int /*<<< orphan*/  len; int /*<<< orphan*/  list; int /*<<< orphan*/  cpu_addr; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  rwlock_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct smc_buf_desc* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct smc_buf_desc*) ; 
 int PTR_ERR (struct smc_buf_desc*) ; 
 int SG_MAX_SINGLE_ALLOC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int get_order (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct smc_buf_desc* smc_buf_get_slot (int,int /*<<< orphan*/ *,struct list_head*) ; 
 int smc_compress_bufsize (int) ; 
 int /*<<< orphan*/  smc_ism_set_conn (struct smc_connection*) ; 
 int /*<<< orphan*/  smc_rmb_wnd_update_limit (int /*<<< orphan*/ ) ; 
 int smc_uncompress_bufsize (int) ; 
 struct smc_buf_desc* smcd_new_buf_create (struct smc_link_group*,int,int) ; 
 struct smc_buf_desc* smcr_new_buf_create (struct smc_link_group*,int,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __smc_buf_create(struct smc_sock *smc, bool is_smcd, bool is_rmb)
{
	struct smc_buf_desc *buf_desc = ERR_PTR(-ENOMEM);
	struct smc_connection *conn = &smc->conn;
	struct smc_link_group *lgr = conn->lgr;
	struct list_head *buf_list;
	int bufsize, bufsize_short;
	int sk_buf_size;
	rwlock_t *lock;

	if (is_rmb)
		/* use socket recv buffer size (w/o overhead) as start value */
		sk_buf_size = smc->sk.sk_rcvbuf / 2;
	else
		/* use socket send buffer size (w/o overhead) as start value */
		sk_buf_size = smc->sk.sk_sndbuf / 2;

	for (bufsize_short = smc_compress_bufsize(sk_buf_size);
	     bufsize_short >= 0; bufsize_short--) {

		if (is_rmb) {
			lock = &lgr->rmbs_lock;
			buf_list = &lgr->rmbs[bufsize_short];
		} else {
			lock = &lgr->sndbufs_lock;
			buf_list = &lgr->sndbufs[bufsize_short];
		}
		bufsize = smc_uncompress_bufsize(bufsize_short);
		if ((1 << get_order(bufsize)) > SG_MAX_SINGLE_ALLOC)
			continue;

		/* check for reusable slot in the link group */
		buf_desc = smc_buf_get_slot(bufsize_short, lock, buf_list);
		if (buf_desc) {
			memset(buf_desc->cpu_addr, 0, bufsize);
			break; /* found reusable slot */
		}

		if (is_smcd)
			buf_desc = smcd_new_buf_create(lgr, is_rmb, bufsize);
		else
			buf_desc = smcr_new_buf_create(lgr, is_rmb, bufsize);

		if (PTR_ERR(buf_desc) == -ENOMEM)
			break;
		if (IS_ERR(buf_desc))
			continue;

		buf_desc->used = 1;
		write_lock_bh(lock);
		list_add(&buf_desc->list, buf_list);
		write_unlock_bh(lock);
		break; /* found */
	}

	if (IS_ERR(buf_desc))
		return -ENOMEM;

	if (is_rmb) {
		conn->rmb_desc = buf_desc;
		conn->rmbe_size_short = bufsize_short;
		smc->sk.sk_rcvbuf = bufsize * 2;
		atomic_set(&conn->bytes_to_rcv, 0);
		conn->rmbe_update_limit =
			smc_rmb_wnd_update_limit(buf_desc->len);
		if (is_smcd)
			smc_ism_set_conn(conn); /* map RMB/smcd_dev to conn */
	} else {
		conn->sndbuf_desc = buf_desc;
		smc->sk.sk_sndbuf = bufsize * 2;
		atomic_set(&conn->sndbuf_space, bufsize);
	}
	return 0;
}