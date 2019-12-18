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
struct TYPE_2__ {int /*<<< orphan*/  (* sample_reset ) (struct snd_emux*) ;} ;
struct snd_emux {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct snd_emux*) ; 

__attribute__((used)) static void sf_sample_reset(void *private_data)
{
	struct snd_emux *emu = private_data;
	emu->ops.sample_reset(emu);
}