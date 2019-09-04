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
struct mp_recorder_sink {int dummy; } ;
struct mp_recorder {int num_streams; struct mp_recorder_sink** streams; } ;

/* Variables and functions */

struct mp_recorder_sink *mp_recorder_get_sink(struct mp_recorder *r, int stream)
{
    return stream >= 0 && stream < r->num_streams ? r->streams[stream] : NULL;
}