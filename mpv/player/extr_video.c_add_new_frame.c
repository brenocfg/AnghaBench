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
struct mp_image {int dummy; } ;
struct MPContext {scalar_t__ num_next_frames; struct mp_image** next_frames; } ;

/* Variables and functions */
 scalar_t__ MP_ARRAY_SIZE (struct mp_image**) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  handle_new_frame (struct MPContext*) ; 

__attribute__((used)) static void add_new_frame(struct MPContext *mpctx, struct mp_image *frame)
{
    assert(mpctx->num_next_frames < MP_ARRAY_SIZE(mpctx->next_frames));
    assert(frame);
    mpctx->next_frames[mpctx->num_next_frames++] = frame;
    if (mpctx->num_next_frames == 1)
        handle_new_frame(mpctx);
}