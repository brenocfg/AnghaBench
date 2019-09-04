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
struct nfsd_net {TYPE_1__* client_tracking_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* grace_done ) (struct nfsd_net*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nfsd_net*) ; 

void
nfsd4_record_grace_done(struct nfsd_net *nn)
{
	if (nn->client_tracking_ops)
		nn->client_tracking_ops->grace_done(nn);
}