#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* media_remux_job_t ;
struct TYPE_3__ {int /*<<< orphan*/  ifmt_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  av_dump_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int avformat_find_stream_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int avformat_open_input (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static inline bool init_input(media_remux_job_t job, const char *in_filename)
{
	int ret = avformat_open_input(&job->ifmt_ctx, in_filename, NULL, NULL);
	if (ret < 0) {
		blog(LOG_ERROR, "media_remux: Could not open input file '%s'",
		     in_filename);
		return false;
	}

	ret = avformat_find_stream_info(job->ifmt_ctx, NULL);
	if (ret < 0) {
		blog(LOG_ERROR, "media_remux: Failed to retrieve input stream"
				" information");
		return false;
	}

#ifndef _NDEBUG
	av_dump_format(job->ifmt_ctx, 0, in_filename, false);
#endif
	return true;
}