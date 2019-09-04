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
struct halmac_api {int dummy; } ;
struct halmac_ampdu_config {int /*<<< orphan*/  max_agg_num; } ;
struct halmac_adapter {scalar_t__ halmac_api; } ;

/* Variables and functions */
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ REG_PROT_MODE_CTRL ; 

void halmac_config_ampdu_88xx(struct halmac_adapter *halmac_adapter,
			      struct halmac_ampdu_config *ampdu_config)
{
	struct halmac_api *halmac_api;

	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	HALMAC_REG_WRITE_8(halmac_adapter, REG_PROT_MODE_CTRL + 2,
			   ampdu_config->max_agg_num);
	HALMAC_REG_WRITE_8(halmac_adapter, REG_PROT_MODE_CTRL + 3,
			   ampdu_config->max_agg_num);
}