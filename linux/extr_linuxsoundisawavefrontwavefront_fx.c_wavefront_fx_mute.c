#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fx_op; } ;
typedef  TYPE_1__ snd_wavefront_t ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wavefront_fx_idle (TYPE_1__*) ; 

__attribute__((used)) static void
wavefront_fx_mute (snd_wavefront_t *dev, int onoff)

{
	if (!wavefront_fx_idle(dev)) {
		return;
	}

	outb (onoff ? 0x02 : 0x00, dev->fx_op);
}