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
struct track {int dummy; } ;
struct MPContext {int dummy; } ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;

/* Variables and functions */
 int /*<<< orphan*/  mp_switch_track_n (struct MPContext*,int /*<<< orphan*/ ,int,struct track*,int) ; 

void mp_switch_track(struct MPContext *mpctx, enum stream_type type,
                     struct track *track, int flags)
{
    mp_switch_track_n(mpctx, 0, type, track, flags);
}