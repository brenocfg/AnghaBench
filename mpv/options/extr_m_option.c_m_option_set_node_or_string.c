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
struct TYPE_2__ {char const* string; } ;
struct mpv_node {scalar_t__ format; TYPE_1__ u; } ;
struct mp_log {int dummy; } ;
typedef  int /*<<< orphan*/  m_option_t ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 scalar_t__ MPV_FORMAT_STRING ; 
 int /*<<< orphan*/  bstr0 (char const*) ; 
 scalar_t__ bstr_split_tok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int m_option_parse (struct mp_log*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int m_option_set_node (int /*<<< orphan*/  const*,void*,struct mpv_node*) ; 

int m_option_set_node_or_string(struct mp_log *log, const m_option_t *opt,
                                const char *name, void *dst, struct mpv_node *src)
{
    if (src->format == MPV_FORMAT_STRING) {
        // The af and vf option unfortunately require this, because the
        // option name includes the "action".
        bstr optname = bstr0(name), a, b;
        if (bstr_split_tok(optname, "/", &a, &b))
            optname = b;
        return m_option_parse(log, opt, optname, bstr0(src->u.string), dst);
    } else {
        return m_option_set_node(opt, dst, src);
    }
}