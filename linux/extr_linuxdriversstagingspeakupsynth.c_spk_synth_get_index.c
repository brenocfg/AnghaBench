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
struct spk_synth {TYPE_1__* io_ops; } ;
struct TYPE_2__ {unsigned char (* synth_in_nowait ) () ;} ;

/* Variables and functions */
 unsigned char stub1 () ; 

unsigned char spk_synth_get_index(struct spk_synth *synth)
{
	return synth->io_ops->synth_in_nowait();
}