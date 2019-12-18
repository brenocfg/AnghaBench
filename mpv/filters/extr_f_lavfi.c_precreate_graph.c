#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lavfi {int failed; int num_all_pads; int /*<<< orphan*/  f; TYPE_1__** all_pads; int /*<<< orphan*/  graph_string; scalar_t__ graph; int /*<<< orphan*/  direct_filter_opts; int /*<<< orphan*/  log; scalar_t__ direct_filter; int /*<<< orphan*/  graph_opts; } ;
struct TYPE_8__ {int /*<<< orphan*/  nb_outputs; int /*<<< orphan*/  output_pads; int /*<<< orphan*/  nb_inputs; int /*<<< orphan*/  input_pads; int /*<<< orphan*/  priv; } ;
struct TYPE_7__ {int /*<<< orphan*/  filter; } ;
typedef  int /*<<< orphan*/  AVFilterInOut ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct lavfi*,char*,...) ; 
 int /*<<< orphan*/  MP_PIN_IN ; 
 int /*<<< orphan*/  MP_PIN_OUT ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  add_pads (struct lavfi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_pads_direct (struct lavfi*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  avfilter_get_by_name (int /*<<< orphan*/ ) ; 
 scalar_t__ avfilter_graph_alloc () ; 
 TYPE_2__* avfilter_graph_alloc_filter (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ avfilter_graph_parse2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ avfilter_init_str (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avfilter_inout_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_graph (struct lavfi*) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_failed (int /*<<< orphan*/ ) ; 
 scalar_t__ mp_set_avopts (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_set_avopts_pos (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void precreate_graph(struct lavfi *c, bool first_init)
{
    assert(!c->graph);

    c->failed = false;

    c->graph = avfilter_graph_alloc();
    if (!c->graph)
        abort();

    if (mp_set_avopts(c->log, c->graph, c->graph_opts) < 0)
        goto error;

    if (c->direct_filter) {
        AVFilterContext *filter = avfilter_graph_alloc_filter(c->graph,
                            avfilter_get_by_name(c->graph_string), "filter");
        if (!filter) {
            MP_FATAL(c, "filter '%s' not found or failed to allocate\n",
                     c->graph_string);
            goto error;
        }

        if (mp_set_avopts_pos(c->log, filter, filter->priv,
                              c->direct_filter_opts) < 0)
            goto error;

        if (avfilter_init_str(filter, NULL) < 0) {
            MP_FATAL(c, "filter failed to initialize\n");
            goto error;
        }

        add_pads_direct(c, MP_PIN_IN, filter, filter->input_pads,
                        filter->nb_inputs, first_init);
        add_pads_direct(c, MP_PIN_OUT, filter, filter->output_pads,
                        filter->nb_outputs, first_init);
    } else {
        AVFilterInOut *in = NULL, *out = NULL;
        if (avfilter_graph_parse2(c->graph, c->graph_string, &in, &out) < 0) {
            MP_FATAL(c, "parsing the filter graph failed\n");
            goto error;
        }
        add_pads(c, MP_PIN_IN, in, first_init);
        add_pads(c, MP_PIN_OUT, out, first_init);
        avfilter_inout_free(&in);
        avfilter_inout_free(&out);
    }

    for (int n = 0; n < c->num_all_pads; n++)
        c->failed |= !c->all_pads[n]->filter;

    if (c->failed)
        goto error;

    return;

error:
    free_graph(c);
    c->failed = true;
    mp_filter_internal_mark_failed(c->f);
    return;
}