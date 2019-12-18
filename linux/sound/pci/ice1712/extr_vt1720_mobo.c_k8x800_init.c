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
struct snd_ice1712 {int vt1720; int num_total_dacs; int num_total_adcs; } ;

/* Variables and functions */

__attribute__((used)) static int k8x800_init(struct snd_ice1712 *ice)
{
	ice->vt1720 = 1;

	/* VT1616 codec */
	ice->num_total_dacs = 6;
	ice->num_total_adcs = 2;

	/* WM8728 codec */
	/* FIXME: TODO */

	return 0;
}