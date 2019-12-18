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
struct hdac_device {int dummy; } ;
struct hdac_chmap {struct hdac_device* hdac; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  chmap_ops ; 
 int /*<<< orphan*/  init_channel_allocations () ; 

void snd_hdac_register_chmap_ops(struct hdac_device *hdac,
				struct hdac_chmap *chmap)
{
	chmap->ops = chmap_ops;
	chmap->hdac = hdac;
	init_channel_allocations();
}