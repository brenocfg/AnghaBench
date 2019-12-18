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
struct hpi_control_cache {struct hpi_control_cache* p_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hpi_control_cache*) ; 

void hpi_free_control_cache(struct hpi_control_cache *p_cache)
{
	if (p_cache) {
		kfree(p_cache->p_info);
		kfree(p_cache);
	}
}