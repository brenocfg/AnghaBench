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
struct vo_chain {scalar_t__ dec_src; scalar_t__* pins; TYPE_2__* filter; scalar_t__ filter_src; struct track* track; } ;
struct track {TYPE_1__* dec; struct vo_chain* vo_c; } ;
struct TYPE_4__ {struct vo_chain* f; } ;
struct TYPE_3__ {struct vo_chain* f; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_pin_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  talloc_free (struct vo_chain*) ; 

__attribute__((used)) static void vo_chain_uninit(struct vo_chain *vo_c)
{
    struct track *track = vo_c->track;
    if (track) {
        assert(track->vo_c == vo_c);
        track->vo_c = NULL;
        if (vo_c->dec_src)
            assert(track->dec->f->pins[0] == vo_c->dec_src);
        talloc_free(track->dec->f);
        track->dec = NULL;
    }

    if (vo_c->filter_src)
        mp_pin_disconnect(vo_c->filter_src);

    talloc_free(vo_c->filter->f);
    talloc_free(vo_c);
    // this does not free the VO
}