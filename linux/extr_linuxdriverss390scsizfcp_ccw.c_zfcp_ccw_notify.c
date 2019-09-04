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
struct zfcp_adapter {int /*<<< orphan*/  status; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  CIO_BOXED 131 
#define  CIO_GONE 130 
#define  CIO_NO_PATH 129 
#define  CIO_OPER 128 
 int ZFCP_STATUS_ADAPTER_SUSPENDED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_RUNNING ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct zfcp_adapter* zfcp_ccw_adapter_by_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  zfcp_ccw_adapter_put (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_basic (char*,struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_shutdown (struct zfcp_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfcp_erp_set_adapter_status (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_ccw_notify(struct ccw_device *cdev, int event)
{
	struct zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);

	if (!adapter)
		return 1;

	switch (event) {
	case CIO_GONE:
		if (atomic_read(&adapter->status) &
		    ZFCP_STATUS_ADAPTER_SUSPENDED) { /* notification ignore */
			zfcp_dbf_hba_basic("ccnigo1", adapter);
			break;
		}
		dev_warn(&cdev->dev, "The FCP device has been detached\n");
		zfcp_erp_adapter_shutdown(adapter, 0, "ccnoti1");
		break;
	case CIO_NO_PATH:
		dev_warn(&cdev->dev,
			 "The CHPID for the FCP device is offline\n");
		zfcp_erp_adapter_shutdown(adapter, 0, "ccnoti2");
		break;
	case CIO_OPER:
		if (atomic_read(&adapter->status) &
		    ZFCP_STATUS_ADAPTER_SUSPENDED) { /* notification ignore */
			zfcp_dbf_hba_basic("ccniop1", adapter);
			break;
		}
		dev_info(&cdev->dev, "The FCP device is operational again\n");
		zfcp_erp_set_adapter_status(adapter,
					    ZFCP_STATUS_COMMON_RUNNING);
		zfcp_erp_adapter_reopen(adapter, ZFCP_STATUS_COMMON_ERP_FAILED,
					"ccnoti4");
		break;
	case CIO_BOXED:
		dev_warn(&cdev->dev, "The FCP device did not respond within "
				     "the specified time\n");
		zfcp_erp_adapter_shutdown(adapter, 0, "ccnoti5");
		break;
	}

	zfcp_ccw_adapter_put(adapter);
	return 1;
}