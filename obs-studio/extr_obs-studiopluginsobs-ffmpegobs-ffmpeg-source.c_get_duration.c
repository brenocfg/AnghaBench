#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* fmt; } ;
struct ffmpeg_source {TYPE_2__ media; } ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  calldata_t ;
struct TYPE_3__ {int duration; } ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_set_int (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void get_duration(void *data, calldata_t *cd)
{
	struct ffmpeg_source *s = data;
	int64_t dur = 0;
	if (s->media.fmt)
		dur = s->media.fmt->duration;

	calldata_set_int(cd, "duration", dur * 1000);
}