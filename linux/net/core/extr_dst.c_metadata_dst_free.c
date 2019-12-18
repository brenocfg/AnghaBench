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
struct TYPE_3__ {int /*<<< orphan*/  dst_cache; } ;
struct TYPE_4__ {TYPE_1__ tun_info; } ;
struct metadata_dst {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ METADATA_IP_TUNNEL ; 
 int /*<<< orphan*/  dst_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct metadata_dst*) ; 

void metadata_dst_free(struct metadata_dst *md_dst)
{
#ifdef CONFIG_DST_CACHE
	if (md_dst->type == METADATA_IP_TUNNEL)
		dst_cache_destroy(&md_dst->u.tun_info.dst_cache);
#endif
	kfree(md_dst);
}