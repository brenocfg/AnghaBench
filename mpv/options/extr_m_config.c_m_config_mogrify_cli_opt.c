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
struct m_option_type {int flags; struct m_option_action* actions; } ;
struct m_option_action {char* name; int flags; } ;
struct m_config_option {char* name; TYPE_1__* opt; } ;
struct m_config {int num_opts; struct m_config_option* opts; } ;
struct bstr {int len; char* start; } ;
typedef  struct bstr bstr ;
struct TYPE_2__ {struct m_option_type* type; scalar_t__ priv; } ;

/* Variables and functions */
 int M_OPT_TYPE_CHOICE ; 
 struct bstr bstr0 (char*) ; 
 scalar_t__ bstr_eatstart0 (struct bstr*,char*) ; 
 scalar_t__ bstr_endswith (struct bstr,struct bstr) ; 
 int /*<<< orphan*/  bstr_startswith (struct bstr,struct bstr) ; 
 struct m_config_option* m_config_get_co (struct m_config*,struct bstr) ; 
 struct m_config_option* m_config_get_co_any (struct m_config*,struct bstr) ; 
 struct m_option_type m_option_type_alias ; 
 struct m_option_type m_option_type_cli_alias ; 

__attribute__((used)) static struct m_config_option *m_config_mogrify_cli_opt(struct m_config *config,
                                                        struct bstr *name,
                                                        bool *out_negate,
                                                        int *out_add_flags)
{
    *out_negate = false;
    *out_add_flags = 0;

    struct m_config_option *co = m_config_get_co(config, *name);
    if (co)
        return co;

    // Turn "--no-foo" into "foo" + set *out_negate.
    bstr no_name = *name;
    if (!co && bstr_eatstart0(&no_name, "no-")) {
        co = m_config_get_co(config, no_name);

        // Not all choice types have this value - if they don't, then parsing
        // them will simply result in an error. Good enough.
        if (!co || !(co->opt->type->flags & M_OPT_TYPE_CHOICE))
            return NULL;

        *name = no_name;
        *out_negate = true;
        return co;
    }

    // Resolve CLI alias. (We don't allow you to combine them with "--no-".)
    co = m_config_get_co_any(config, *name);
    if (co && co->opt->type == &m_option_type_cli_alias)
        *name = bstr0((char *)co->opt->priv);

    // Might be a suffix "action", like "--vf-add". Expensively check for
    // matches. (We don't allow you to combine them with "--no-".)
    for (int n = 0; n < config->num_opts; n++) {
        co = &config->opts[n];
        struct bstr basename = bstr0(co->name);

        if (!bstr_startswith(*name, basename))
            continue;

        // Aliased option + a suffix action, e.g. --opengl-shaders-append
        if (co->opt->type == &m_option_type_alias)
            co = m_config_get_co_any(config, basename);
        if (!co)
            continue;

        const struct m_option_type *type = co->opt->type;
        for (int i = 0; type->actions && type->actions[i].name; i++) {
            const struct m_option_action *action = &type->actions[i];
            bstr suffix = bstr0(action->name);

            if (bstr_endswith(*name, suffix) &&
                (name->len == basename.len + 1 + suffix.len) &&
                name->start[basename.len] == '-')
            {
                *out_add_flags = action->flags;
                return co;
            }
        }
    }

    return NULL;
}