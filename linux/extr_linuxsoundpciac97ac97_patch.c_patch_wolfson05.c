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
struct snd_ac97 {int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  patch_wolfson_wm9703_ops ; 

__attribute__((used)) static int patch_wolfson05(struct snd_ac97 * ac97)
{
	/* WM9705, WM9710 */
	ac97->build_ops = &patch_wolfson_wm9703_ops;
#ifdef CONFIG_TOUCHSCREEN_WM9705
	/* WM9705 touchscreen uses AUX and VIDEO for touch */
	ac97->flags |= AC97_HAS_NO_VIDEO | AC97_HAS_NO_AUX;
#endif
	return 0;
}