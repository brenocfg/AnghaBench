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
struct snd_info_buffer {int dummy; } ;
struct snd_ff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_clock_config (struct snd_ff*,struct snd_info_buffer*) ; 
 int /*<<< orphan*/  dump_sync_status (struct snd_ff*,struct snd_info_buffer*) ; 

__attribute__((used)) static void former_dump_status(struct snd_ff *ff,
			       struct snd_info_buffer *buffer)
{
	dump_clock_config(ff, buffer);
	dump_sync_status(ff, buffer);
}