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
struct TYPE_2__ {int dev_desc; int pwr_desc; int geom_desc; int conf_desc; int unit_desc; int interc_desc; int hlth_desc; } ;
struct ufs_hba {TYPE_1__ desc_size; } ;
typedef  enum desc_idn { ____Placeholder_desc_idn } desc_idn ;

/* Variables and functions */
 int EINVAL ; 
#define  QUERY_DESC_IDN_CONFIGURATION 137 
#define  QUERY_DESC_IDN_DEVICE 136 
#define  QUERY_DESC_IDN_GEOMETRY 135 
#define  QUERY_DESC_IDN_HEALTH 134 
#define  QUERY_DESC_IDN_INTERCONNECT 133 
#define  QUERY_DESC_IDN_POWER 132 
#define  QUERY_DESC_IDN_RFU_0 131 
#define  QUERY_DESC_IDN_RFU_1 130 
#define  QUERY_DESC_IDN_STRING 129 
#define  QUERY_DESC_IDN_UNIT 128 
 int QUERY_DESC_MAX_SIZE ; 

int ufshcd_map_desc_id_to_length(struct ufs_hba *hba,
	enum desc_idn desc_id, int *desc_len)
{
	switch (desc_id) {
	case QUERY_DESC_IDN_DEVICE:
		*desc_len = hba->desc_size.dev_desc;
		break;
	case QUERY_DESC_IDN_POWER:
		*desc_len = hba->desc_size.pwr_desc;
		break;
	case QUERY_DESC_IDN_GEOMETRY:
		*desc_len = hba->desc_size.geom_desc;
		break;
	case QUERY_DESC_IDN_CONFIGURATION:
		*desc_len = hba->desc_size.conf_desc;
		break;
	case QUERY_DESC_IDN_UNIT:
		*desc_len = hba->desc_size.unit_desc;
		break;
	case QUERY_DESC_IDN_INTERCONNECT:
		*desc_len = hba->desc_size.interc_desc;
		break;
	case QUERY_DESC_IDN_STRING:
		*desc_len = QUERY_DESC_MAX_SIZE;
		break;
	case QUERY_DESC_IDN_HEALTH:
		*desc_len = hba->desc_size.hlth_desc;
		break;
	case QUERY_DESC_IDN_RFU_0:
	case QUERY_DESC_IDN_RFU_1:
		*desc_len = 0;
		break;
	default:
		*desc_len = 0;
		return -EINVAL;
	}
	return 0;
}