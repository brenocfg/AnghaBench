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
struct ffmpeg_data {scalar_t__ last_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (scalar_t__) ; 
 scalar_t__ bstrdup (char const*) ; 

__attribute__((used)) static void ffmpeg_output_set_last_error(struct ffmpeg_data *data,
					 const char *error)
{
	if (data->last_error)
		bfree(data->last_error);

	data->last_error = bstrdup(error);
}