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
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; } ;
struct skl_module_cfg {int dummy; } ;
struct skl_debug {int /*<<< orphan*/  modules; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct skl_module_cfg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcfg_fops ; 

void skl_debug_init_module(struct skl_debug *d,
			struct snd_soc_dapm_widget *w,
			struct skl_module_cfg *mconfig)
{
	debugfs_create_file(w->name, 0444, d->modules, mconfig,
			    &mcfg_fops);
}