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
struct nfsd_net {struct cld_net* cld_net; } ;
struct net {int dummy; } ;
struct cld_net {scalar_t__ cn_tfm; int /*<<< orphan*/  cn_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cld_net*) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_cld_unregister_net (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  rpc_destroy_pipe_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfsd4_remove_cld_pipe(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	struct cld_net *cn = nn->cld_net;

	nfsd4_cld_unregister_net(net, cn->cn_pipe);
	rpc_destroy_pipe_data(cn->cn_pipe);
	if (cn->cn_tfm)
		crypto_free_shash(cn->cn_tfm);
	kfree(nn->cld_net);
	nn->cld_net = NULL;
}