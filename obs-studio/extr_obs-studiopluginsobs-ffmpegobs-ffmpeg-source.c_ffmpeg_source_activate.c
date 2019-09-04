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
struct ffmpeg_source {scalar_t__ restart_on_activate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ffmpeg_source_start (struct ffmpeg_source*) ; 

__attribute__((used)) static void ffmpeg_source_activate(void *data)
{
	struct ffmpeg_source *s = data;

	if (s->restart_on_activate)
		ffmpeg_source_start(s);
}