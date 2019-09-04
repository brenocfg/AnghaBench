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
struct nvme_dev {int cmbsz; } ;

/* Variables and functions */
 int NVME_CMBSZ_SZ_MASK ; 
 int NVME_CMBSZ_SZ_SHIFT ; 

__attribute__((used)) static u32 nvme_cmb_size(struct nvme_dev *dev)
{
	return (dev->cmbsz >> NVME_CMBSZ_SZ_SHIFT) & NVME_CMBSZ_SZ_MASK;
}