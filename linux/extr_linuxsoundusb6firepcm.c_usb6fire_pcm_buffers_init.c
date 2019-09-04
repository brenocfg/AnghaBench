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
struct TYPE_4__ {void* buffer; } ;
struct TYPE_3__ {void* buffer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCM_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  PCM_N_PACKETS_PER_URB ; 
 int PCM_N_URBS ; 
 void* kcalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb6fire_pcm_buffers_init(struct pcm_runtime *rt)
{
	int i;

	for (i = 0; i < PCM_N_URBS; i++) {
		rt->out_urbs[i].buffer = kcalloc(PCM_MAX_PACKET_SIZE,
						 PCM_N_PACKETS_PER_URB,
						 GFP_KERNEL);
		if (!rt->out_urbs[i].buffer)
			return -ENOMEM;
		rt->in_urbs[i].buffer = kcalloc(PCM_MAX_PACKET_SIZE,
						PCM_N_PACKETS_PER_URB,
						GFP_KERNEL);
		if (!rt->in_urbs[i].buffer)
			return -ENOMEM;
	}
	return 0;
}