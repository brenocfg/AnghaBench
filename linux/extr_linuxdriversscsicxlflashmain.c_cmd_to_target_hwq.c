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
typedef  int u32 ;
struct scsi_cmnd {int /*<<< orphan*/  request; } ;
struct afu {int num_hwqs; int hwq_mode; int /*<<< orphan*/  hwq_rr_count; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
#define  HWQ_MODE_CPU 130 
#define  HWQ_MODE_RR 129 
#define  HWQ_MODE_TAG 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int blk_mq_unique_tag (int /*<<< orphan*/ ) ; 
 int blk_mq_unique_tag_to_hwq (int) ; 
 int smp_processor_id () ; 

__attribute__((used)) static u32 cmd_to_target_hwq(struct Scsi_Host *host, struct scsi_cmnd *scp,
			     struct afu *afu)
{
	u32 tag;
	u32 hwq = 0;

	if (afu->num_hwqs == 1)
		return 0;

	switch (afu->hwq_mode) {
	case HWQ_MODE_RR:
		hwq = afu->hwq_rr_count++ % afu->num_hwqs;
		break;
	case HWQ_MODE_TAG:
		tag = blk_mq_unique_tag(scp->request);
		hwq = blk_mq_unique_tag_to_hwq(tag);
		break;
	case HWQ_MODE_CPU:
		hwq = smp_processor_id() % afu->num_hwqs;
		break;
	default:
		WARN_ON_ONCE(1);
	}

	return hwq;
}