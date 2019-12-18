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
struct snd_soc_component {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sessions; } ;
struct TYPE_3__ {int port_id; int fedai_id; } ;

/* Variables and functions */
 int MAX_SESSIONS ; 
 TYPE_2__* routing_data ; 

__attribute__((used)) static int msm_routing_probe(struct snd_soc_component *c)
{
	int i;

	for (i = 0; i < MAX_SESSIONS; i++) {
		routing_data->sessions[i].port_id = -1;
		routing_data->sessions[i].fedai_id = -1;
	}

	return 0;
}