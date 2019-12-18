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
struct TYPE_2__ {int (* get_data ) (struct snd_ice1712*) ;} ;
struct snd_ice1712 {TYPE_1__ gpio; } ;

/* Variables and functions */
 int GPIO_INTERNAL_CLOCK ; 
 int stub1 (struct snd_ice1712*) ; 

__attribute__((used)) static inline int juli_is_spdif_master(struct snd_ice1712 *ice)
{
	return (ice->gpio.get_data(ice) & GPIO_INTERNAL_CLOCK) ? 0 : 1;
}