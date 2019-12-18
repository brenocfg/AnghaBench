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
struct splice_pipe_desc {int nr_pages_max; int nr_pages; int /*<<< orphan*/  spd_release; int /*<<< orphan*/ * ops; struct partial_page* partial; int /*<<< orphan*/ * pages; } ;
struct smc_spd_priv {size_t len; struct smc_sock* smc; } ;
struct TYPE_4__ {int /*<<< orphan*/  splice_pending; TYPE_1__* rmb_desc; } ;
struct smc_sock {TYPE_2__ conn; int /*<<< orphan*/  sk; } ;
struct pipe_inode_info {int dummy; } ;
struct partial_page {int offset; size_t len; unsigned long private; } ;
struct TYPE_3__ {int /*<<< orphan*/  pages; scalar_t__ cpu_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 struct smc_spd_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_pipe_ops ; 
 int /*<<< orphan*/  smc_rx_spd_release ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ *) ; 
 int splice_to_pipe (struct pipe_inode_info*,struct splice_pipe_desc*) ; 

__attribute__((used)) static int smc_rx_splice(struct pipe_inode_info *pipe, char *src, size_t len,
			 struct smc_sock *smc)
{
	struct splice_pipe_desc spd;
	struct partial_page partial;
	struct smc_spd_priv *priv;
	int bytes;

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	priv->len = len;
	priv->smc = smc;
	partial.offset = src - (char *)smc->conn.rmb_desc->cpu_addr;
	partial.len = len;
	partial.private = (unsigned long)priv;

	spd.nr_pages_max = 1;
	spd.nr_pages = 1;
	spd.pages = &smc->conn.rmb_desc->pages;
	spd.partial = &partial;
	spd.ops = &smc_pipe_ops;
	spd.spd_release = smc_rx_spd_release;

	bytes = splice_to_pipe(pipe, &spd);
	if (bytes > 0) {
		sock_hold(&smc->sk);
		get_page(smc->conn.rmb_desc->pages);
		atomic_add(bytes, &smc->conn.splice_pending);
	}

	return bytes;
}