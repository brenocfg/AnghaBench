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
struct hdac_ext_bus_ops {int dummy; } ;

/* Variables and functions */
 struct hdac_ext_bus_ops hdac_ops ; 

struct hdac_ext_bus_ops *snd_soc_hdac_hda_get_ops(void)
{
	return &hdac_ops;
}