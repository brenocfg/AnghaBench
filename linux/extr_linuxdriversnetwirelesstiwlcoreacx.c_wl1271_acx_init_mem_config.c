#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wl1271_acx_mem_map {int dummy; } ;
struct wl1271 {int /*<<< orphan*/  tx_blocks_available; TYPE_1__* target_mem_map; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_tx_mem_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int wl1271_acx_mem_map (struct wl1271*,void*,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl1271_acx_init_mem_config(struct wl1271 *wl)
{
	int ret;

	wl->target_mem_map = kzalloc(sizeof(struct wl1271_acx_mem_map),
				     GFP_KERNEL);
	if (!wl->target_mem_map) {
		wl1271_error("couldn't allocate target memory map");
		return -ENOMEM;
	}

	/* we now ask for the firmware built memory map */
	ret = wl1271_acx_mem_map(wl, (void *)wl->target_mem_map,
				 sizeof(struct wl1271_acx_mem_map));
	if (ret < 0) {
		wl1271_error("couldn't retrieve firmware memory map");
		kfree(wl->target_mem_map);
		wl->target_mem_map = NULL;
		return ret;
	}

	/* initialize TX block book keeping */
	wl->tx_blocks_available =
		le32_to_cpu(wl->target_mem_map->num_tx_mem_blocks);
	wl1271_debug(DEBUG_TX, "available tx blocks: %d",
		     wl->tx_blocks_available);

	return 0;
}