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
struct nfs4_replay {int /*<<< orphan*/  rp_mutex; int /*<<< orphan*/  rp_ibuf; int /*<<< orphan*/  rp_buf; scalar_t__ rp_buflen; int /*<<< orphan*/  rp_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfserr_serverfault ; 

__attribute__((used)) static void init_nfs4_replay(struct nfs4_replay *rp)
{
	rp->rp_status = nfserr_serverfault;
	rp->rp_buflen = 0;
	rp->rp_buf = rp->rp_ibuf;
	mutex_init(&rp->rp_mutex);
}