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
struct demuxer {scalar_t__ duration; } ;
struct MPContext {struct demuxer* demuxer; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 

double get_time_length(struct MPContext *mpctx)
{
    struct demuxer *demuxer = mpctx->demuxer;
    return demuxer && demuxer->duration >= 0 ? demuxer->duration : MP_NOPTS_VALUE;
}