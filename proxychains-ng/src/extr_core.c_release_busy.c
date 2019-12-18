#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ps; } ;
typedef  TYPE_1__ proxy_data ;

/* Variables and functions */
 scalar_t__ BUSY_STATE ; 
 scalar_t__ PLAY_STATE ; 

__attribute__((used)) static void release_busy(proxy_data * pd, unsigned int proxy_count) {
	unsigned int i;
	for(i = 0; i < proxy_count; i++)
		if(pd[i].ps == BUSY_STATE)
			pd[i].ps = PLAY_STATE;
	return;
}