#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mp_filter_command {scalar_t__ speed; int /*<<< orphan*/  type; } ;
struct mp_filter {struct aspeed_priv* priv; } ;
struct TYPE_4__ {scalar_t__ filter; } ;
struct aspeed_priv {TYPE_1__ sub; scalar_t__ cur_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  MP_FILTER_COMMAND_SET_SPEED ; 
 int /*<<< orphan*/  MP_OUTPUT_CHAIN_AUDIO ; 
 int /*<<< orphan*/  MP_VERBOSE (struct mp_filter*,char*) ; 
 int fabs (scalar_t__) ; 
 scalar_t__ mp_create_user_filter (struct mp_filter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_filter_command (scalar_t__,struct mp_filter_command*) ; 
 int /*<<< orphan*/  mp_subfilter_continue (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_subfilter_drain_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_subfilter_read (TYPE_1__*) ; 

__attribute__((used)) static void aspeed_process(struct mp_filter *f)
{
    struct aspeed_priv *p = f->priv;

    if (!mp_subfilter_read(&p->sub))
        return;

    if (fabs(p->cur_speed - 1.0) < 1e-8) {
        if (p->sub.filter)
            MP_VERBOSE(f, "removing scaletempo\n");
        if (!mp_subfilter_drain_destroy(&p->sub))
            return;
    } else if (!p->sub.filter) {
        MP_VERBOSE(f, "adding scaletempo\n");
        p->sub.filter =
            mp_create_user_filter(f, MP_OUTPUT_CHAIN_AUDIO, "scaletempo", NULL);
        if (!p->sub.filter) {
            MP_ERR(f, "could not create scaletempo filter\n");
            mp_subfilter_continue(&p->sub);
            return;
        }
    }

    if (p->sub.filter) {
        struct mp_filter_command cmd = {
            .type = MP_FILTER_COMMAND_SET_SPEED,
            .speed = p->cur_speed,
        };
        mp_filter_command(p->sub.filter, &cmd);
    }

    mp_subfilter_continue(&p->sub);
}