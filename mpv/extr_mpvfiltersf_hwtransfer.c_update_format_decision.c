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
struct mp_hwupload {int* upload_fmts; int num_upload_fmts; int num_fmts; int* fmt_upload_index; int* fmt_upload_num; int* fmts; int /*<<< orphan*/  f; } ;
struct priv {int last_input_fmt; int last_upload_fmt; int last_sw_fmt; struct mp_hwupload public; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_INFO (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mp_imgfmt_select_best_list (int*,int,int) ; 
 int /*<<< orphan*/  mp_imgfmt_to_name (int) ; 

__attribute__((used)) static bool update_format_decision(struct priv *p, int input_fmt)
{
    struct mp_hwupload *u = &p->public;

    if (!input_fmt)
        return false;

    if (input_fmt == p->last_input_fmt)
        return true;

    p->last_input_fmt = 0;

    int res = mp_imgfmt_select_best_list(u->upload_fmts, u->num_upload_fmts,
                                         input_fmt);

    if (!res)
        return false;

    // Find which sw format we should use.
    // NOTE: if there are ever any hw APIs that actually do expensive
    // conversions on mismatching format uploads, we should probably first look
    // which sw format is preferred?
    int index = -1;
    for (int n = 0; n < u->num_upload_fmts; n++) {
        if (u->upload_fmts[n] == res)
            index = n;
    }

    if (index < 0)
        return false;

    for (int n = 0; n < u->num_fmts; n++) {
        if (index >= u->fmt_upload_index[n] &&
            index < u->fmt_upload_index[n] + u->fmt_upload_num[n])
        {
            p->last_input_fmt = input_fmt;
            p->last_upload_fmt = u->upload_fmts[index];
            p->last_sw_fmt = u->fmts[n];
            MP_INFO(u->f, "upload %s -> %s (%s)\n",
                    mp_imgfmt_to_name(p->last_input_fmt),
                    mp_imgfmt_to_name(p->last_upload_fmt),
                    mp_imgfmt_to_name(p->last_sw_fmt));
            return true;
        }
    }

    return false;
}