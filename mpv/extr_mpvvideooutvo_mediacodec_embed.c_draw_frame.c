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
struct vo_frame {int /*<<< orphan*/  current; int /*<<< orphan*/  repeat; int /*<<< orphan*/  redraw; } ;
struct vo {struct priv* priv; } ;
struct priv {int /*<<< orphan*/ * next_image; } ;
typedef  int /*<<< orphan*/  mp_image_t ;

/* Variables and functions */
 int /*<<< orphan*/ * mp_image_new_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void draw_frame(struct vo *vo, struct vo_frame *frame)
{
    struct priv *p = vo->priv;

    mp_image_t *mpi = NULL;
    if (!frame->redraw && !frame->repeat)
        mpi = mp_image_new_ref(frame->current);

    talloc_free(p->next_image);
    p->next_image = mpi;
}