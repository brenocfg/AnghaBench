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
struct ffmpeg_mux {TYPE_1__* output; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** streams; } ;
typedef  int /*<<< orphan*/  AVStream ;

/* Variables and functions */

__attribute__((used)) static inline AVStream *get_stream(struct ffmpeg_mux *ffm, int idx)
{
	return ffm->output->streams[idx];
}