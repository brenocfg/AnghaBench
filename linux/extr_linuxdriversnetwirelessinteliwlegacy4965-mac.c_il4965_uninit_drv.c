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
struct il_priv {int /*<<< orphan*/  scan_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  il_free_channel_map (struct il_priv*) ; 
 int /*<<< orphan*/  il_free_geos (struct il_priv*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
il4965_uninit_drv(struct il_priv *il)
{
	il_free_geos(il);
	il_free_channel_map(il);
	kfree(il->scan_cmd);
}