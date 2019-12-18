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
struct vo_frame {int num_frames; int /*<<< orphan*/ ** frames; int /*<<< orphan*/ * current; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  destroy_frame ; 
 int /*<<< orphan*/ * mp_image_new_ref (int /*<<< orphan*/ *) ; 
 struct vo_frame* new ; 
 struct vo_frame* talloc_ptrtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_set_destructor (struct vo_frame*,int /*<<< orphan*/ ) ; 

struct vo_frame *vo_frame_ref(struct vo_frame *frame)
{
    if (!frame)
        return NULL;

    struct vo_frame *new = talloc_ptrtype(NULL, new);
    talloc_set_destructor(new, destroy_frame);
    *new = *frame;
    for (int n = 0; n < frame->num_frames; n++) {
        new->frames[n] = mp_image_new_ref(frame->frames[n]);
        if (!new->frames[n])
            abort(); // OOM on tiny allocs
    }
    new->current = new->num_frames ? new->frames[0] : NULL;
    return new;
}