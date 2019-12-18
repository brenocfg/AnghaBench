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
struct mp_log {int dummy; } ;
struct m_obj_settings {int dummy; } ;
struct m_config_option {int /*<<< orphan*/  opt; int /*<<< orphan*/  data; } ;
struct MPContext {int /*<<< orphan*/  mconfig; } ;
typedef  int /*<<< orphan*/  optname ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 char* BSTR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr0 (char const*) ; 
 char const** filter_opt ; 
 struct m_config_option* m_config_get_co (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_option_copy (int /*<<< orphan*/ ,struct m_obj_settings**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_option_free (int /*<<< orphan*/ ,struct m_obj_settings**) ; 
 int m_option_parse (struct mp_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct m_obj_settings**) ; 
 int set_filters (struct MPContext*,int,struct m_obj_settings*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

__attribute__((used)) static int edit_filters(struct MPContext *mpctx, struct mp_log *log,
                        enum stream_type mediatype,
                        const char *cmd, const char *arg)
{
    bstr option = bstr0(filter_opt[mediatype]);
    struct m_config_option *co = m_config_get_co(mpctx->mconfig, option);
    if (!co)
        return -1;

    // The option parser is used to modify the filter list itself.
    char optname[20];
    snprintf(optname, sizeof(optname), "%.*s-%s", BSTR_P(option), cmd);

    struct m_obj_settings *new_chain = NULL;
    m_option_copy(co->opt, &new_chain, co->data);

    int r = m_option_parse(log, co->opt, bstr0(optname), bstr0(arg), &new_chain);
    if (r >= 0)
        r = set_filters(mpctx, mediatype, new_chain);

    m_option_free(co->opt, &new_chain);

    return r >= 0 ? 0 : -1;
}