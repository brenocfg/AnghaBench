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
struct MPContext {int num_next_frames; int /*<<< orphan*/ * next_frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shift_frames(struct MPContext *mpctx)
{
    if (mpctx->num_next_frames < 1)
        return;
    talloc_free(mpctx->next_frames[0]);
    for (int n = 0; n < mpctx->num_next_frames - 1; n++)
        mpctx->next_frames[n] = mpctx->next_frames[n + 1];
    mpctx->num_next_frames -= 1;
}