#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mp_filter {struct lavfi* priv; } ;
struct lavfi {int num_out_pads; int /*<<< orphan*/  f; scalar_t__ failed; TYPE_1__** out_pads; scalar_t__ draining_recover; scalar_t__ initialized; } ;
struct TYPE_2__ {int buffer_is_eof; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct lavfi*,char*) ; 
 int feed_input_pads (struct lavfi*) ; 
 int /*<<< orphan*/  free_graph (struct lavfi*) ; 
 int /*<<< orphan*/  init_graph (struct lavfi*) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_failed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_progress (int /*<<< orphan*/ ) ; 
 int read_output_pads (struct lavfi*) ; 

__attribute__((used)) static void lavfi_process(struct mp_filter *f)
{
    struct lavfi *c = f->priv;

    if (!c->initialized)
        init_graph(c);

    while (c->initialized) {
        bool a = read_output_pads(c);
        bool b = feed_input_pads(c);
        if (!a && !b)
            break;
    }

    // Start over on format changes or EOF draining.
    if (c->draining_recover) {
        // Wait until all outputs got EOF.
        bool all_eof = true;
        for (int n = 0; n < c->num_out_pads; n++)
            all_eof &= c->out_pads[n]->buffer_is_eof;

        if (all_eof) {
            MP_VERBOSE(c, "recovering all eof\n");
            free_graph(c);
            mp_filter_internal_mark_progress(c->f);
        }
    }

    if (c->failed)
        mp_filter_internal_mark_failed(c->f);
}