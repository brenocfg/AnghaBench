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
struct MPContext {int /*<<< orphan*/ ** current_track; } ;

/* Variables and functions */
 int NUM_PTRACKS ; 
 size_t STREAM_SUB ; 
 int /*<<< orphan*/  reinit_sub (struct MPContext*,int /*<<< orphan*/ ) ; 

void reinit_sub_all(struct MPContext *mpctx)
{
    for (int n = 0; n < NUM_PTRACKS; n++)
        reinit_sub(mpctx, mpctx->current_track[n][STREAM_SUB]);
}