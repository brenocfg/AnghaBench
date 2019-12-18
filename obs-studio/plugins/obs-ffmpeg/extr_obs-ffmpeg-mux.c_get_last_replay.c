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
struct TYPE_2__ {int /*<<< orphan*/  array; } ;
struct ffmpeg_muxer {TYPE_1__ path; int /*<<< orphan*/  muxing; } ;
typedef  int /*<<< orphan*/  calldata_t ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_set_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_atomic_load_bool (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_last_replay(void *data, calldata_t *cd)
{
	struct ffmpeg_muxer *stream = data;
	if (!os_atomic_load_bool(&stream->muxing))
		calldata_set_string(cd, "path", stream->path.array);
}