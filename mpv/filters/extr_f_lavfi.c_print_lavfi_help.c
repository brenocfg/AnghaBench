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
struct mp_log {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * priv_class; } ;
struct TYPE_7__ {scalar_t__ type; int offset; int /*<<< orphan*/  help; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ AVOption ;
typedef  TYPE_2__ AVFilter ;
typedef  int /*<<< orphan*/  AVClass ;

/* Variables and functions */
 scalar_t__ AV_OPT_TYPE_CONST ; 
 int /*<<< orphan*/  NSTR (int /*<<< orphan*/ ) ; 
 TYPE_1__* av_opt_next (int /*<<< orphan*/  const**,TYPE_1__ const*) ; 
 TYPE_2__* avfilter_get_by_name (char const*) ; 
 char* get_avopt_type_name (scalar_t__) ; 
 int /*<<< orphan*/  is_usable (TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  mp_err (struct mp_log*,char*,char const*) ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 
 char* mp_tprintf (int,char*,char const*) ; 

void print_lavfi_help(struct mp_log *log, const char *name, int media_type)
{
    const AVFilter *f = avfilter_get_by_name(name);
    if (!f) {
        mp_err(log, "Filter '%s' not found.\n", name);
        return;
    }
    if (!is_usable(f, media_type)) {
        mp_err(log, "Filter '%s' is not usable in this context (wrong media \n"
               "types or wrong number of inputs/outputs).\n", name);
    }
    mp_info(log, "Options:\n\n");
    const AVClass *class = f->priv_class;
    // av_opt_next() requires this for some retarded incomprehensible reason.
    const AVClass **c = &class;
    int offset= -1;
    int count = 0;
    for (const AVOption *o = av_opt_next(c, 0); o; o = av_opt_next(c, o)) {
        // This is how libavfilter (at the time) decided to assign positional
        // options (called "shorthand" in the libavfilter code). So we
        // duplicate it exactly.
        if (o->type == AV_OPT_TYPE_CONST || o->offset == offset)
            continue;
        offset = o->offset;

        const char *t = get_avopt_type_name(o->type);
        char *tstr = t ? mp_tprintf(30, "<%s>", t) : "?";
        mp_info(log, " %-10s %-12s %s\n", o->name, tstr, NSTR(o->help));

        const AVOption *sub = o;
        while (1) {
            sub = av_opt_next(c, sub);
            if (!sub || sub->type != AV_OPT_TYPE_CONST)
                break;
            mp_info(log, " %3s%-23s %s\n", "", sub->name, NSTR(sub->help));
        }

        count++;
    }
    mp_info(log, "\nTotal: %d options\n", count);
}