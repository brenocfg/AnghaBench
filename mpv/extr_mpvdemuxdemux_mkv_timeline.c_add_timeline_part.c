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
typedef  int uint64_t ;
struct tl_ctx {int last_end_time; int num_parts; int start_time; TYPE_2__* timeline; TYPE_1__* opts; } ;
struct timeline_part {int start; int source_start; struct demuxer* source; } ;
struct demuxer {int dummy; } ;
typedef  int int64_t ;
struct TYPE_4__ {struct demuxer* source; } ;
struct TYPE_3__ {int chapter_merge_threshold; } ;

/* Variables and functions */
 int FFABS (int) ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,TYPE_2__*,int,struct timeline_part) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct tl_ctx*,char*,int,int) ; 

__attribute__((used)) static int64_t add_timeline_part(struct tl_ctx *ctx,
                                 struct demuxer *source,
                                 uint64_t start)
{
    /* Merge directly adjacent parts. We allow for a configurable fudge factor
     * because of files which specify chapter end times that are one frame too
     * early; we don't want to try seeking over a one frame gap. */
    int64_t join_diff = start - ctx->last_end_time;
    if (ctx->num_parts == 0
        || FFABS(join_diff) > ctx->opts->chapter_merge_threshold * 1e6
        || source != ctx->timeline[ctx->num_parts - 1].source)
    {
        struct timeline_part new = {
            .start = ctx->start_time / 1e9,
            .source_start = start / 1e9,
            .source = source,
        };
        MP_TARRAY_APPEND(NULL, ctx->timeline, ctx->num_parts, new);
    } else if (ctx->num_parts > 0 && join_diff) {
        // Chapter was merged at an inexact boundary; adjust timestamps to match.
        MP_VERBOSE(ctx, "Merging timeline part %d with offset %g ms.\n",
                   ctx->num_parts, join_diff / 1e6);
        ctx->start_time += join_diff;
        return join_diff;
    }

    return 0;
}