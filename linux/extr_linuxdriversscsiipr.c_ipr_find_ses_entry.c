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
struct ipr_std_inq_vpids {scalar_t__* product_id; } ;
struct ipr_ses_table_entry {char* compare_product_id_byte; scalar_t__* product_id; } ;
struct TYPE_2__ {struct ipr_std_inq_vpids vpids; } ;
struct ipr_resource_entry {TYPE_1__ std_inq_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ipr_ses_table_entry*) ; 
 int IPR_PROD_ID_LEN ; 
 struct ipr_ses_table_entry* ipr_ses_table ; 

__attribute__((used)) static const struct ipr_ses_table_entry *
ipr_find_ses_entry(struct ipr_resource_entry *res)
{
	int i, j, matches;
	struct ipr_std_inq_vpids *vpids;
	const struct ipr_ses_table_entry *ste = ipr_ses_table;

	for (i = 0; i < ARRAY_SIZE(ipr_ses_table); i++, ste++) {
		for (j = 0, matches = 0; j < IPR_PROD_ID_LEN; j++) {
			if (ste->compare_product_id_byte[j] == 'X') {
				vpids = &res->std_inq_data.vpids;
				if (vpids->product_id[j] == ste->product_id[j])
					matches++;
				else
					break;
			} else
				matches++;
		}

		if (matches == IPR_PROD_ID_LEN)
			return ste;
	}

	return NULL;
}