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
struct ima_template_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IMA_DEFAULT_TEMPLATE ; 
 int /*<<< orphan*/  ima_init_template_list () ; 
 struct ima_template_desc* ima_template ; 
 struct ima_template_desc* lookup_template_desc (int /*<<< orphan*/ ) ; 

struct ima_template_desc *ima_template_desc_current(void)
{
	if (!ima_template) {
		ima_init_template_list();
		ima_template =
		    lookup_template_desc(CONFIG_IMA_DEFAULT_TEMPLATE);
	}
	return ima_template;
}