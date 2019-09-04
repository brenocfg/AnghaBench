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
struct hisi_sas_dq {int id; int wr_point; } ;
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DLVRY_Q_0_RD_PTR ; 
 int EAGAIN ; 
 int HISI_SAS_QUEUE_SLOTS ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int hisi_sas_read32_relaxed (struct hisi_hba*,scalar_t__) ; 

__attribute__((used)) static int
get_free_slot_v1_hw(struct hisi_hba *hisi_hba, struct hisi_sas_dq *dq)
{
	struct device *dev = hisi_hba->dev;
	int queue = dq->id;
	u32 r, w;

	w = dq->wr_point;
	r = hisi_sas_read32_relaxed(hisi_hba,
				DLVRY_Q_0_RD_PTR + (queue * 0x14));
	if (r == (w+1) % HISI_SAS_QUEUE_SLOTS) {
		dev_warn(dev, "could not find free slot\n");
		return -EAGAIN;
	}

	dq->wr_point = (dq->wr_point + 1) % HISI_SAS_QUEUE_SLOTS;

	return w;
}