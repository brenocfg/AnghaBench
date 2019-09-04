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
typedef  int /*<<< orphan*/  u64 ;
struct vio_dev {int /*<<< orphan*/  unit_address; } ;
struct ibmvscsi_host_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_SEND_CRQ ; 
 int /*<<< orphan*/  mb () ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vio_dev* to_vio_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvscsi_send_crq(struct ibmvscsi_host_data *hostdata,
			     u64 word1, u64 word2)
{
	struct vio_dev *vdev = to_vio_dev(hostdata->dev);

	/*
	 * Ensure the command buffer is flushed to memory before handing it
	 * over to the VIOS to prevent it from fetching any stale data.
	 */
	mb();
	return plpar_hcall_norets(H_SEND_CRQ, vdev->unit_address, word1, word2);
}