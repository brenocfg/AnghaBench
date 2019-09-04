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
struct mp_lavfi {struct mp_filter* f; } ;
struct mp_filter {struct lavfi* priv; } ;
struct lavfi_user_opts {int /*<<< orphan*/  fix_pts; int /*<<< orphan*/  graph; int /*<<< orphan*/  avopts; int /*<<< orphan*/  type; int /*<<< orphan*/  filter_opts; int /*<<< orphan*/  filter_name; scalar_t__ is_bridge; } ;
struct lavfi {int /*<<< orphan*/  emulate_audio_pts; } ;

/* Variables and functions */
 struct mp_lavfi* mp_lavfi_create_filter (struct mp_filter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mp_lavfi* mp_lavfi_create_graph (struct mp_filter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (struct lavfi_user_opts*) ; 

__attribute__((used)) static struct mp_filter *lavfi_create(struct mp_filter *parent, void *options)
{
    struct lavfi_user_opts *opts = options;
    struct mp_lavfi *l;
    if (opts->is_bridge) {
        l = mp_lavfi_create_filter(parent, opts->type, true, opts->avopts,
                                   opts->filter_name, opts->filter_opts);
    } else {
        l = mp_lavfi_create_graph(parent, opts->type, true,
                                  opts->avopts, opts->graph);
    }
    if (l) {
        struct lavfi *c = l->f->priv;
        c->emulate_audio_pts = opts->fix_pts;
    }
    talloc_free(opts);
    return l ? l->f : NULL;
}