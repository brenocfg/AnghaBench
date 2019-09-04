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
struct metadata_dst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct metadata_dst*) ; 

void metadata_dst_free(struct metadata_dst *md_dst)
{
#ifdef CONFIG_DST_CACHE
	if (md_dst->type == METADATA_IP_TUNNEL)
		dst_cache_destroy(&md_dst->u.tun_info.dst_cache);
#endif
	kfree(md_dst);
}