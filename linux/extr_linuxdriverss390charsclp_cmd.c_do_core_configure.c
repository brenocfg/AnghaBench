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
struct TYPE_2__ {int length; int response_code; } ;
struct cpu_configure_sccb {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  sclp_cmdw_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SCLP_HAS_CPU_RECONFIG ; 
 int /*<<< orphan*/  SCLP_QUEUE_INTERVAL ; 
 int /*<<< orphan*/  kfree (struct cpu_configure_sccb*) ; 
 struct cpu_configure_sccb* kzalloc (int,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int sclp_sync_request_timeout (int /*<<< orphan*/ ,struct cpu_configure_sccb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_core_configure(sclp_cmdw_t cmd)
{
	struct cpu_configure_sccb *sccb;
	int rc;

	if (!SCLP_HAS_CPU_RECONFIG)
		return -EOPNOTSUPP;
	/*
	 * This is not going to cross a page boundary since we force
	 * kmalloc to have a minimum alignment of 8 bytes on s390.
	 */
	sccb = kzalloc(sizeof(*sccb), GFP_KERNEL | GFP_DMA);
	if (!sccb)
		return -ENOMEM;
	sccb->header.length = sizeof(*sccb);
	rc = sclp_sync_request_timeout(cmd, sccb, SCLP_QUEUE_INTERVAL);
	if (rc)
		goto out;
	switch (sccb->header.response_code) {
	case 0x0020:
	case 0x0120:
		break;
	default:
		pr_warn("configure cpu failed (cmd=0x%08x, response=0x%04x)\n",
			cmd, sccb->header.response_code);
		rc = -EIO;
		break;
	}
out:
	kfree(sccb);
	return rc;
}