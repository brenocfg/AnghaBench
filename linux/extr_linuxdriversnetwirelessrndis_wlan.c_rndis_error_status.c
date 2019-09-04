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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  RNDIS_STATUS_ADAPTER_NOT_OPEN 133 
#define  RNDIS_STATUS_ADAPTER_NOT_READY 132 
#define  RNDIS_STATUS_FAILURE 131 
#define  RNDIS_STATUS_INVALID_DATA 130 
#define  RNDIS_STATUS_NOT_SUPPORTED 129 
#define  RNDIS_STATUS_SUCCESS 128 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rndis_error_status(__le32 rndis_status)
{
	int ret = -EINVAL;
	switch (le32_to_cpu(rndis_status)) {
	case RNDIS_STATUS_SUCCESS:
		ret = 0;
		break;
	case RNDIS_STATUS_FAILURE:
	case RNDIS_STATUS_INVALID_DATA:
		ret = -EINVAL;
		break;
	case RNDIS_STATUS_NOT_SUPPORTED:
		ret = -EOPNOTSUPP;
		break;
	case RNDIS_STATUS_ADAPTER_NOT_READY:
	case RNDIS_STATUS_ADAPTER_NOT_OPEN:
		ret = -EBUSY;
		break;
	}
	return ret;
}