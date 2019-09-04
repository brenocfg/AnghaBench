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
struct async_delay_data {int dummy; } ;
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_audio_data (struct async_delay_data*) ; 
 int /*<<< orphan*/  free_video_data (struct async_delay_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void async_delay_filter_remove(void *data, obs_source_t *parent)
{
	struct async_delay_data *filter = data;

	free_video_data(filter, parent);
	free_audio_data(filter);
}