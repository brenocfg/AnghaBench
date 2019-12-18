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
union m_option_value {int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  string; } ;
struct mpv_node {scalar_t__ format; TYPE_1__ u; } ;
struct m_config_option {int /*<<< orphan*/  opt; } ;
struct m_config {int /*<<< orphan*/  log; } ;
typedef  int /*<<< orphan*/  bstr ;
struct TYPE_4__ {char* (* print ) (int /*<<< orphan*/ *,struct mpv_node*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BSTR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MPV_FORMAT_STRING ; 
 int /*<<< orphan*/  MP_DBG (struct m_config*,char*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  MSGL_V ; 
 int M_OPT_UNKNOWN ; 
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 struct m_config_option* m_config_get_co (struct m_config*,int /*<<< orphan*/ ) ; 
 int m_config_set_option_raw (struct m_config*,struct m_config_option*,union m_option_value*,int) ; 
 int /*<<< orphan*/  m_option_free (int /*<<< orphan*/ ,union m_option_value*) ; 
 int m_option_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union m_option_value*) ; 
 int m_option_set_node (int /*<<< orphan*/ ,union m_option_value*,struct mpv_node*) ; 
 TYPE_2__ m_option_type_node ; 
 scalar_t__ mp_msg_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_null_log ; 
 char* stub1 (int /*<<< orphan*/ *,struct mpv_node*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

int m_config_set_option_node(struct m_config *config, bstr name,
                             struct mpv_node *data, int flags)
{
    int r;

    struct m_config_option *co = m_config_get_co(config, name);
    if (!co)
        return M_OPT_UNKNOWN;

    // Do this on an "empty" type to make setting the option strictly overwrite
    // the old value, as opposed to e.g. appending to lists.
    union m_option_value val = {0};

    if (data->format == MPV_FORMAT_STRING) {
        bstr param = bstr0(data->u.string);
        r = m_option_parse(mp_null_log, co->opt, name, param, &val);
    } else {
        r = m_option_set_node(co->opt, &val, data);
    }

    if (r >= 0)
        r = m_config_set_option_raw(config, co, &val, flags);

    if (mp_msg_test(config->log, MSGL_V)) {
        char *s = m_option_type_node.print(NULL, data);
        MP_DBG(config, "Setting option '%.*s' = %s (flags = %d) -> %d\n",
               BSTR_P(name), s ? s : "?", flags, r);
        talloc_free(s);
    }

    m_option_free(co->opt, &val);
    return r;
}