#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipr_ioa_cfg {int nvectors; TYPE_2__* vectors_info; TYPE_1__* host; } ;
struct TYPE_4__ {scalar_t__* desc; } ;
struct TYPE_3__ {int host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (scalar_t__*,int,char*,int,int) ; 
 size_t strlen (scalar_t__*) ; 

__attribute__((used)) static void name_msi_vectors(struct ipr_ioa_cfg *ioa_cfg)
{
	int vec_idx, n = sizeof(ioa_cfg->vectors_info[0].desc) - 1;

	for (vec_idx = 0; vec_idx < ioa_cfg->nvectors; vec_idx++) {
		snprintf(ioa_cfg->vectors_info[vec_idx].desc, n,
			 "host%d-%d", ioa_cfg->host->host_no, vec_idx);
		ioa_cfg->vectors_info[vec_idx].
			desc[strlen(ioa_cfg->vectors_info[vec_idx].desc)] = 0;
	}
}