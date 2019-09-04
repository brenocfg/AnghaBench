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
struct wl1271 {int dummy; } ;
struct acx_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_MEM_MAP ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int wl1271_cmd_interrogate (struct wl1271*,int /*<<< orphan*/ ,struct acx_header*,int,size_t) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 

int wl1271_acx_mem_map(struct wl1271 *wl, struct acx_header *mem_map,
		       size_t len)
{
	int ret;

	wl1271_debug(DEBUG_ACX, "acx mem map");

	ret = wl1271_cmd_interrogate(wl, ACX_MEM_MAP, mem_map,
				     sizeof(struct acx_header), len);
	if (ret < 0)
		return ret;

	return 0;
}