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
struct ff_demuxer {int seek_request; int seek_flush; int /*<<< orphan*/  input; TYPE_1__* format_context; scalar_t__ seek_pos; int /*<<< orphan*/  seek_flags; } ;
struct TYPE_2__ {scalar_t__ duration; scalar_t__ start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVSEEK_FLAG_BACKWARD ; 
 int /*<<< orphan*/  AVSEEK_FLAG_FRAME ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seek_beginning(struct ff_demuxer *demuxer)
{
	if (demuxer->format_context->duration == AV_NOPTS_VALUE) {
		demuxer->seek_flags = AVSEEK_FLAG_FRAME;
		demuxer->seek_pos = 0;
	} else {
		demuxer->seek_flags = AVSEEK_FLAG_BACKWARD;
		demuxer->seek_pos = demuxer->format_context->start_time;
	}
	demuxer->seek_request = true;
	demuxer->seek_flush = false;
	av_log(NULL, AV_LOG_VERBOSE, "looping media %s", demuxer->input);
}