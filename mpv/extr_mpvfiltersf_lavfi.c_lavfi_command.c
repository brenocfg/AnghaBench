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
struct mp_tags {int dummy; } ;
struct mp_filter_command {int type; struct mp_tags** res; } ;
struct mp_filter {struct lavfi* priv; } ;
struct lavfi {int num_out_pads; TYPE_1__** out_pads; int /*<<< orphan*/  initialized; } ;
struct TYPE_2__ {int /*<<< orphan*/  metadata; } ;

/* Variables and functions */
#define  MP_FILTER_COMMAND_GET_META 128 
 struct mp_tags* mp_tags_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool lavfi_command(struct mp_filter *f, struct mp_filter_command *cmd)
{
    struct lavfi *c = f->priv;

    if (!c->initialized)
        return false;

    switch (cmd->type) {
#if LIBAVFILTER_VERSION_MICRO >= 100
    case MP_FILTER_COMMAND_TEXT: {
        return avfilter_graph_send_command(c->graph, "all", cmd->cmd, cmd->arg,
                                           &(char){0}, 0, 0) >= 0;
    }
#endif
    case MP_FILTER_COMMAND_GET_META: {
        // We can worry later about what it should do to multi output filters.
        if (c->num_out_pads < 1)
            return false;
        struct mp_tags **ptags = cmd->res;
        *ptags = mp_tags_dup(NULL, c->out_pads[0]->metadata);
        return true;
    }
    default:
        return false;
    }
}