#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int int64_t ;
struct TYPE_4__ {scalar_t__ block_size; } ;
typedef  TYPE_1__ audio_t ;

/* Variables and functions */
 int ts_diff_frames (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t ts_diff_bytes(const audio_t *audio, uint64_t ts1, uint64_t ts2)
{
	return ts_diff_frames(audio, ts1, ts2) * (int64_t)audio->block_size;
}