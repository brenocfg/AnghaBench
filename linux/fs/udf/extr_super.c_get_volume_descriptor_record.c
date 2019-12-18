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
typedef  int uint16_t ;
struct udf_vds_record {int dummy; } ;
struct desc_seq_scan_data {struct udf_vds_record* vds; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
#define  TAG_IDENT_IUVD 132 
#define  TAG_IDENT_LVD 131 
#define  TAG_IDENT_PD 130 
#define  TAG_IDENT_PVD 129 
#define  TAG_IDENT_USD 128 
 size_t VDS_POS_IMP_USE_VOL_DESC ; 
 size_t VDS_POS_LOGICAL_VOL_DESC ; 
 size_t VDS_POS_PRIMARY_VOL_DESC ; 
 size_t VDS_POS_UNALLOC_SPACE_DESC ; 
 struct udf_vds_record* handle_partition_descriptor (struct buffer_head*,struct desc_seq_scan_data*) ; 

__attribute__((used)) static struct udf_vds_record *get_volume_descriptor_record(uint16_t ident,
		struct buffer_head *bh, struct desc_seq_scan_data *data)
{
	switch (ident) {
	case TAG_IDENT_PVD: /* ISO 13346 3/10.1 */
		return &(data->vds[VDS_POS_PRIMARY_VOL_DESC]);
	case TAG_IDENT_IUVD: /* ISO 13346 3/10.4 */
		return &(data->vds[VDS_POS_IMP_USE_VOL_DESC]);
	case TAG_IDENT_LVD: /* ISO 13346 3/10.6 */
		return &(data->vds[VDS_POS_LOGICAL_VOL_DESC]);
	case TAG_IDENT_USD: /* ISO 13346 3/10.8 */
		return &(data->vds[VDS_POS_UNALLOC_SPACE_DESC]);
	case TAG_IDENT_PD: /* ISO 13346 3/10.5 */
		return handle_partition_descriptor(bh, data);
	}
	return NULL;
}