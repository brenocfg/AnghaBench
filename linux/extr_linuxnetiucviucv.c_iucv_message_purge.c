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
struct TYPE_2__ {int ipsrccls; int ipflags1; int /*<<< orphan*/  ipmsgtag; int /*<<< orphan*/  ipaudit; int /*<<< orphan*/  ipmsgid; int /*<<< orphan*/  ippathid; } ;
union iucv_param {TYPE_1__ purge; } ;
typedef  int u32 ;
struct iucv_path {int /*<<< orphan*/  pathid; } ;
struct iucv_message {int audit; int /*<<< orphan*/  tag; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EIO ; 
 int IUCV_IPFGMID ; 
 int IUCV_IPFGPID ; 
 int IUCV_IPSRCCLS ; 
 int /*<<< orphan*/  IUCV_PURGE ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iucv_buffer_cpumask ; 
 int iucv_call_b2f0 (int /*<<< orphan*/ ,union iucv_param*) ; 
 union iucv_param** iucv_param ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  memset (union iucv_param*,int /*<<< orphan*/ ,int) ; 
 size_t smp_processor_id () ; 

int iucv_message_purge(struct iucv_path *path, struct iucv_message *msg,
		       u32 srccls)
{
	union iucv_param *parm;
	int rc;

	local_bh_disable();
	if (cpumask_empty(&iucv_buffer_cpumask)) {
		rc = -EIO;
		goto out;
	}
	parm = iucv_param[smp_processor_id()];
	memset(parm, 0, sizeof(union iucv_param));
	parm->purge.ippathid = path->pathid;
	parm->purge.ipmsgid = msg->id;
	parm->purge.ipsrccls = srccls;
	parm->purge.ipflags1 = IUCV_IPSRCCLS | IUCV_IPFGMID | IUCV_IPFGPID;
	rc = iucv_call_b2f0(IUCV_PURGE, parm);
	if (!rc) {
		msg->audit = (*(u32 *) &parm->purge.ipaudit) >> 8;
		msg->tag = parm->purge.ipmsgtag;
	}
out:
	local_bh_enable();
	return rc;
}