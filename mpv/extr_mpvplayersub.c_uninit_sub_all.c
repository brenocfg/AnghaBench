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
struct MPContext {int num_tracks; int /*<<< orphan*/ * tracks; } ;

/* Variables and functions */
 int /*<<< orphan*/  uninit_sub (struct MPContext*,int /*<<< orphan*/ ) ; 

void uninit_sub_all(struct MPContext *mpctx)
{
    for (int n = 0; n < mpctx->num_tracks; n++)
        uninit_sub(mpctx, mpctx->tracks[n]);
}