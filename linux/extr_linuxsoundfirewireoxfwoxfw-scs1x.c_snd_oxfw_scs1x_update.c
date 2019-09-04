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
struct snd_oxfw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  register_address (struct snd_oxfw*) ; 

void snd_oxfw_scs1x_update(struct snd_oxfw *oxfw)
{
	register_address(oxfw);
}