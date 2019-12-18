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
struct v4l2_data {int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_source_set_async_unbuffered (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void v4l2_update_source_flags(struct v4l2_data *data,
				     obs_data_t *settings)
{
	obs_source_set_async_unbuffered(
		data->source, !obs_data_get_bool(settings, "buffering"));
}