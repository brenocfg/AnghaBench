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
struct mpv_global {int dummy; } ;
struct mp_log {int dummy; } ;
struct m_obj_desc {int /*<<< orphan*/  (* set_defaults ) (struct mpv_global*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  options; int /*<<< orphan*/  priv_defaults; int /*<<< orphan*/  priv_size; } ;
struct m_config {int /*<<< orphan*/  optstruct; struct mpv_global* global; } ;

/* Variables and functions */
 struct m_config* m_config_new (void*,struct mp_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mpv_global*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct m_config *m_config_from_obj_desc(void *talloc_ctx,
                                               struct mp_log *log,
                                               struct mpv_global *global,
                                               struct m_obj_desc *desc)
{
    struct m_config *c =
        m_config_new(talloc_ctx, log, desc->priv_size, desc->priv_defaults,
                     desc->options);
    c->global = global;
    if (desc->set_defaults && c->global)
        desc->set_defaults(c->global, c->optstruct);
    return c;
}