#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcm_runtime {TYPE_2__* in_urbs; TYPE_1__* out_urbs; } ;
struct TYPE_4__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int PCM_N_URBS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb6fire_pcm_buffers_destroy(struct pcm_runtime *rt)
{
	int i;

	for (i = 0; i < PCM_N_URBS; i++) {
		kfree(rt->out_urbs[i].buffer);
		kfree(rt->in_urbs[i].buffer);
	}
}