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
struct qedf_ctx {int /*<<< orphan*/  mac; } ;
struct qed_generic_tlvs {int /*<<< orphan*/ * mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDF_LOG_EVT ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qed_generic_tlvs*,int /*<<< orphan*/ ,int) ; 

void qedf_get_generic_tlv_data(void *dev, struct qed_generic_tlvs *data)
{
	struct qedf_ctx *qedf;

	if (!dev) {
		QEDF_INFO(NULL, QEDF_LOG_EVT,
			  "dev is NULL so ignoring get_generic_tlv_data request.\n");
		return;
	}
	qedf = (struct qedf_ctx *)dev;

	memset(data, 0, sizeof(struct qed_generic_tlvs));
	ether_addr_copy(data->mac[0], qedf->mac);
}