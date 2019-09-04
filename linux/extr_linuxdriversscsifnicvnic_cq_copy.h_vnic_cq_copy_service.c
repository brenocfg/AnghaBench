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
typedef  int u8 ;
struct TYPE_2__ {int desc_size; int desc_count; scalar_t__ descs; } ;
struct vnic_cq {int to_clean; int last_color; struct vnic_dev* vdev; unsigned int index; TYPE_1__ ring; } ;
typedef  struct fcpio_fw_req fcpio_fw_req ;

/* Variables and functions */
 int /*<<< orphan*/  fcpio_color_dec (struct fcpio_fw_req*,int*) ; 
 int stub1 (struct vnic_dev*,unsigned int,struct fcpio_fw_req*) ; 

__attribute__((used)) static inline unsigned int vnic_cq_copy_service(
	struct vnic_cq *cq,
	int (*q_service)(struct vnic_dev *vdev,
			 unsigned int index,
			 struct fcpio_fw_req *desc),
	unsigned int work_to_do)

{
	struct fcpio_fw_req *desc;
	unsigned int work_done = 0;
	u8 color;

	desc = (struct fcpio_fw_req *)((u8 *)cq->ring.descs +
		cq->ring.desc_size * cq->to_clean);
	fcpio_color_dec(desc, &color);

	while (color != cq->last_color) {

		if ((*q_service)(cq->vdev, cq->index, desc))
			break;

		cq->to_clean++;
		if (cq->to_clean == cq->ring.desc_count) {
			cq->to_clean = 0;
			cq->last_color = cq->last_color ? 0 : 1;
		}

		desc = (struct fcpio_fw_req *)((u8 *)cq->ring.descs +
			cq->ring.desc_size * cq->to_clean);
		fcpio_color_dec(desc, &color);

		work_done++;
		if (work_done >= work_to_do)
			break;
	}

	return work_done;
}