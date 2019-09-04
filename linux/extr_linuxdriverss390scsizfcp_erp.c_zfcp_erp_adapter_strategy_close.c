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
struct zfcp_erp_action {struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; int /*<<< orphan*/  gs; scalar_t__ fsf_req_seq_no; int /*<<< orphan*/  qdio; } ;

/* Variables and functions */
 int ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED ; 
 int ZFCP_STATUS_ADAPTER_XCONFIG_OK ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_OPEN ; 
 int /*<<< orphan*/  atomic_andnot (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_clear_adapter_status (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fc_wka_ports_force_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fsf_req_dismiss_all (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_qdio_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_erp_adapter_strategy_close(struct zfcp_erp_action *act)
{
	struct zfcp_adapter *adapter = act->adapter;

	/* close queues to ensure that buffers are not accessed by adapter */
	zfcp_qdio_close(adapter->qdio);
	zfcp_fsf_req_dismiss_all(adapter);
	adapter->fsf_req_seq_no = 0;
	zfcp_fc_wka_ports_force_offline(adapter->gs);
	/* all ports and LUNs are closed */
	zfcp_erp_clear_adapter_status(adapter, ZFCP_STATUS_COMMON_OPEN);

	atomic_andnot(ZFCP_STATUS_ADAPTER_XCONFIG_OK |
			  ZFCP_STATUS_ADAPTER_LINK_UNPLUGGED, &adapter->status);
}