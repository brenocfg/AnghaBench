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
struct lavfi_pad {int filter_pad; int buffer_is_eof; int /*<<< orphan*/  in_fmt; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * filter; } ;
struct lavfi {int num_all_pads; int initialized; int draining_recover; scalar_t__ delay; scalar_t__ in_samples; int /*<<< orphan*/  in_pts; struct lavfi_pad** all_pads; int /*<<< orphan*/  graph; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  avfilter_graph_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_frame_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_graph(struct lavfi *c)
{
    avfilter_graph_free(&c->graph);
    for (int n = 0; n < c->num_all_pads; n++) {
        struct lavfi_pad *pad = c->all_pads[n];

        pad->filter = NULL;
        pad->filter_pad = -1;
        pad->buffer = NULL;
        mp_frame_unref(&pad->in_fmt);
        pad->buffer_is_eof = false;
    }
    c->initialized = false;
    c->draining_recover = false;
    c->in_pts = MP_NOPTS_VALUE;
    c->in_samples = 0;
    c->delay = 0;
}