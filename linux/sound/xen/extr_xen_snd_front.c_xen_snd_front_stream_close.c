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
struct xensnd_req {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  req_io_lock; } ;
struct TYPE_4__ {TYPE_1__ req; } ;
struct xen_snd_front_evtchnl {TYPE_2__ u; int /*<<< orphan*/  ring_io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  XENSND_OP_CLOSE ; 
 int be_stream_do_io (struct xen_snd_front_evtchnl*) ; 
 struct xensnd_req* be_stream_prepare_req (struct xen_snd_front_evtchnl*,int /*<<< orphan*/ ) ; 
 int be_stream_wait_io (struct xen_snd_front_evtchnl*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int xen_snd_front_stream_close(struct xen_snd_front_evtchnl *evtchnl)
{
	struct xensnd_req *req;
	int ret;

	mutex_lock(&evtchnl->u.req.req_io_lock);

	mutex_lock(&evtchnl->ring_io_lock);
	req = be_stream_prepare_req(evtchnl, XENSND_OP_CLOSE);
	mutex_unlock(&evtchnl->ring_io_lock);

	ret = be_stream_do_io(evtchnl);

	if (ret == 0)
		ret = be_stream_wait_io(evtchnl);

	mutex_unlock(&evtchnl->u.req.req_io_lock);
	return ret;
}