#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* media_remux_job_t ;
struct TYPE_8__ {int /*<<< orphan*/  pb; TYPE_1__* oformat; } ;
struct TYPE_7__ {TYPE_5__* ofmt_ctx; int /*<<< orphan*/  ifmt_ctx; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int AVFMT_NOFILE ; 
 int /*<<< orphan*/  avformat_close_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_5__*) ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfree (TYPE_2__*) ; 

void media_remux_job_destroy(media_remux_job_t job)
{
	if (!job)
		return;

	avformat_close_input(&job->ifmt_ctx);

	if (job->ofmt_ctx && !(job->ofmt_ctx->oformat->flags & AVFMT_NOFILE))
		avio_close(job->ofmt_ctx->pb);

	avformat_free_context(job->ofmt_ctx);

	bfree(job);
}