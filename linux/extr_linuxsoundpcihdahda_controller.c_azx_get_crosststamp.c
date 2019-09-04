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
struct system_device_crosststamp {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  azx_get_sync_time ; 
 int get_device_system_crosststamp (int /*<<< orphan*/ ,struct snd_pcm_substream*,int /*<<< orphan*/ *,struct system_device_crosststamp*) ; 

__attribute__((used)) static int azx_get_crosststamp(struct snd_pcm_substream *substream,
			      struct system_device_crosststamp *xtstamp)
{
	return get_device_system_crosststamp(azx_get_sync_time,
					substream, NULL, xtstamp);
}