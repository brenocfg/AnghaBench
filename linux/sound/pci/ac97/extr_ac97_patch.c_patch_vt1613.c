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
struct snd_ac97 {int /*<<< orphan*/  caps; int /*<<< orphan*/  flags; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_BC_HEADPHONE ; 
 int /*<<< orphan*/  AC97_HAS_NO_VIDEO ; 
 int /*<<< orphan*/  patch_vt1613_ops ; 

__attribute__((used)) static int patch_vt1613(struct snd_ac97 *ac97)
{
	ac97->build_ops = &patch_vt1613_ops;

	ac97->flags |= AC97_HAS_NO_VIDEO;
	ac97->caps |= AC97_BC_HEADPHONE;

	return 0;
}