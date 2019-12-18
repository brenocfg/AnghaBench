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
 int /*<<< orphan*/  patch_sigmatel_stac9700_ops ; 

__attribute__((used)) static int patch_sigmatel_stac9700(struct snd_ac97 * ac97)
{
	ac97->build_ops = &patch_sigmatel_stac9700_ops;
	return 0;
}