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
struct mp_output_chain {TYPE_1__* f; } ;
struct mp_chmap {int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int ao_needs_update; int /*<<< orphan*/  output_aformat; } ;
struct chain {TYPE_2__ public; int /*<<< orphan*/  convert; struct ao* ao; } ;
struct ao {int dummy; } ;
struct TYPE_3__ {struct chain* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ao_get_format (struct ao*,int*,int*,struct mp_chmap*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mp_aframe_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_autoconvert_add_afmt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_autoconvert_add_chmap (int /*<<< orphan*/ ,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_autoconvert_add_srate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_autoconvert_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_autoconvert_format_change_continue (int /*<<< orphan*/ ) ; 

void mp_output_chain_set_ao(struct mp_output_chain *c, struct ao *ao)
{
    struct chain *p = c->f->priv;

    assert(p->public.ao_needs_update); // can't just call it any time
    assert(!p->ao);

    p->public.ao_needs_update = false;

    p->ao = ao;

    int out_format = 0;
    int out_rate = 0;
    struct mp_chmap out_channels = {0};
    ao_get_format(p->ao, &out_rate, &out_format, &out_channels);

    mp_autoconvert_clear(p->convert);
    mp_autoconvert_add_afmt(p->convert, out_format);
    mp_autoconvert_add_srate(p->convert, out_rate);
    mp_autoconvert_add_chmap(p->convert, &out_channels);

    mp_autoconvert_format_change_continue(p->convert);

    // Just to get the format change logged again.
    mp_aframe_reset(p->public.output_aformat);
}