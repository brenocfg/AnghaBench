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
struct rpc_pipe {scalar_t__ nwriters; scalar_t__ nreaders; } ;
struct nfsd_net {struct cld_net* cld_net; } ;
struct cld_net {struct rpc_pipe* cn_pipe; } ;

/* Variables and functions */

__attribute__((used)) static bool
cld_running(struct nfsd_net *nn)
{
	struct cld_net *cn = nn->cld_net;
	struct rpc_pipe *pipe = cn->cn_pipe;

	return pipe->nreaders || pipe->nwriters;
}