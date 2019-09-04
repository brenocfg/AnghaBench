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
struct halmac_adapter {int sdio_cmd53_4byte; } ;
typedef  enum halmac_sdio_cmd53_4byte_mode { ____Placeholder_halmac_sdio_cmd53_4byte_mode } halmac_sdio_cmd53_4byte_mode ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int HALMAC_RET_SUCCESS ; 

enum halmac_ret_status
halmac_sdio_cmd53_4byte_88xx(struct halmac_adapter *halmac_adapter,
			     enum halmac_sdio_cmd53_4byte_mode cmd53_4byte_mode)
{
	halmac_adapter->sdio_cmd53_4byte = cmd53_4byte_mode;

	return HALMAC_RET_SUCCESS;
}