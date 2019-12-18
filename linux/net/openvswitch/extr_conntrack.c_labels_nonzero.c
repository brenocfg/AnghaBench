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
struct ovs_key_ct_labels {scalar_t__* ct_labels_32; } ;

/* Variables and functions */
 size_t OVS_CT_LABELS_LEN_32 ; 

__attribute__((used)) static bool labels_nonzero(const struct ovs_key_ct_labels *labels)
{
	size_t i;

	for (i = 0; i < OVS_CT_LABELS_LEN_32; i++)
		if (labels->ct_labels_32[i])
			return true;

	return false;
}