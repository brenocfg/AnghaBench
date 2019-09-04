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
typedef  int u32 ;
struct TYPE_2__ {int size; size_t mapping_sel; int /*<<< orphan*/ * mapping; } ;
struct xenvif {TYPE_1__ hash; } ;

/* Variables and functions */
 int XEN_NETBK_MAX_HASH_MAPPING_SIZE ; 
 int XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER ; 
 int XEN_NETIF_CTRL_STATUS_SUCCESS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

u32 xenvif_set_hash_mapping_size(struct xenvif *vif, u32 size)
{
	if (size > XEN_NETBK_MAX_HASH_MAPPING_SIZE)
		return XEN_NETIF_CTRL_STATUS_INVALID_PARAMETER;

	vif->hash.size = size;
	memset(vif->hash.mapping[vif->hash.mapping_sel], 0,
	       sizeof(u32) * size);

	return XEN_NETIF_CTRL_STATUS_SUCCESS;
}