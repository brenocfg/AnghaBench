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
struct svcxprt_rdma {int sc_snd_w_inv; } ;
struct rpcrdma_connect_private {scalar_t__ cp_magic; scalar_t__ cp_version; int cp_flags; int /*<<< orphan*/  cp_recv_size; int /*<<< orphan*/  cp_send_size; } ;
struct rdma_conn_param {struct rpcrdma_connect_private* private_data; } ;

/* Variables and functions */
 int RPCRDMA_CMP_F_SND_W_INV_OK ; 
 scalar_t__ RPCRDMA_CMP_VERSION ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rpcrdma_cmp_magic ; 
 int /*<<< orphan*/  rpcrdma_decode_buffer_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
svc_rdma_parse_connect_private(struct svcxprt_rdma *newxprt,
			       struct rdma_conn_param *param)
{
	const struct rpcrdma_connect_private *pmsg = param->private_data;

	if (pmsg &&
	    pmsg->cp_magic == rpcrdma_cmp_magic &&
	    pmsg->cp_version == RPCRDMA_CMP_VERSION) {
		newxprt->sc_snd_w_inv = pmsg->cp_flags &
					RPCRDMA_CMP_F_SND_W_INV_OK;

		dprintk("svcrdma: client send_size %u, recv_size %u "
			"remote inv %ssupported\n",
			rpcrdma_decode_buffer_size(pmsg->cp_send_size),
			rpcrdma_decode_buffer_size(pmsg->cp_recv_size),
			newxprt->sc_snd_w_inv ? "" : "un");
	}
}