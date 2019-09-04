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
struct xen_snd_front_info {int dummy; } ;

/* Variables and functions */
 int xen_snd_front_alsa_init (struct xen_snd_front_info*) ; 

__attribute__((used)) static int sndback_connect(struct xen_snd_front_info *front_info)
{
	return xen_snd_front_alsa_init(front_info);
}