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

/* Variables and functions */
 int /*<<< orphan*/  av_register_all () ; 
 int /*<<< orphan*/  avcodec_register_all () ; 
 int /*<<< orphan*/  avformat_network_init () ; 

void ff_init()
{
	av_register_all();
	//avdevice_register_all();
	avcodec_register_all();
	avformat_network_init();
}