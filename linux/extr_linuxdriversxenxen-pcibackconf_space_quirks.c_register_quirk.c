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
struct xen_pcibk_config_quirk {int /*<<< orphan*/  quirks_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_pcibk_quirks ; 

__attribute__((used)) static inline void register_quirk(struct xen_pcibk_config_quirk *quirk)
{
	list_add_tail(&quirk->quirks_list, &xen_pcibk_quirks);
}