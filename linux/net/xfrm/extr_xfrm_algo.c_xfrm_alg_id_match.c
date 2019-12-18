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
struct TYPE_2__ {unsigned long sadb_alg_id; } ;
struct xfrm_algo_desc {TYPE_1__ desc; } ;

/* Variables and functions */

__attribute__((used)) static int xfrm_alg_id_match(const struct xfrm_algo_desc *entry,
			     const void *data)
{
	return entry->desc.sadb_alg_id == (unsigned long)data;
}