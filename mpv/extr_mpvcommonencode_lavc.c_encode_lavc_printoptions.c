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
struct mp_log {int dummy; } ;
typedef  int /*<<< orphan*/  optbuf ;
struct TYPE_4__ {int flags; int type; char* unit; char* name; int /*<<< orphan*/  help; } ;
typedef  TYPE_1__ AVOption ;

/* Variables and functions */
#define  AV_OPT_TYPE_BINARY 136 
#define  AV_OPT_TYPE_CONST 135 
#define  AV_OPT_TYPE_DOUBLE 134 
#define  AV_OPT_TYPE_FLAGS 133 
#define  AV_OPT_TYPE_FLOAT 132 
#define  AV_OPT_TYPE_INT 131 
#define  AV_OPT_TYPE_INT64 130 
#define  AV_OPT_TYPE_RATIONAL 129 
#define  AV_OPT_TYPE_STRING 128 
 TYPE_1__* av_opt_next (void const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  mp_info (struct mp_log*,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void encode_lavc_printoptions(struct mp_log *log, const void *obj,
                                     const char *indent, const char *subindent,
                                     const char *unit, int filter_and,
                                     int filter_eq)
{
    const AVOption *opt = NULL;
    char optbuf[32];
    while ((opt = av_opt_next(obj, opt))) {
        // if flags are 0, it simply hasn't been filled in yet and may be
        // potentially useful
        if (opt->flags)
            if ((opt->flags & filter_and) != filter_eq)
                continue;
        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        if (!unit && opt->type == AV_OPT_TYPE_CONST) {
            continue;
        } else if (unit && opt->type != AV_OPT_TYPE_CONST) {
            continue;
        } else if (unit && opt->type == AV_OPT_TYPE_CONST
                 && strcmp(unit, opt->unit))
        {
            continue;
        } else if (unit && opt->type == AV_OPT_TYPE_CONST) {
            mp_info(log, "%s", subindent);
        } else {
            mp_info(log, "%s", indent);
        }

        switch (opt->type) {
        case AV_OPT_TYPE_FLAGS:
            snprintf(optbuf, sizeof(optbuf), "%s=<flags>", opt->name);
            break;
        case AV_OPT_TYPE_INT:
            snprintf(optbuf, sizeof(optbuf), "%s=<int>", opt->name);
            break;
        case AV_OPT_TYPE_INT64:
            snprintf(optbuf, sizeof(optbuf), "%s=<int64>", opt->name);
            break;
        case AV_OPT_TYPE_DOUBLE:
            snprintf(optbuf, sizeof(optbuf), "%s=<double>", opt->name);
            break;
        case AV_OPT_TYPE_FLOAT:
            snprintf(optbuf, sizeof(optbuf), "%s=<float>", opt->name);
            break;
        case AV_OPT_TYPE_STRING:
            snprintf(optbuf, sizeof(optbuf), "%s=<string>", opt->name);
            break;
        case AV_OPT_TYPE_RATIONAL:
            snprintf(optbuf, sizeof(optbuf), "%s=<rational>", opt->name);
            break;
        case AV_OPT_TYPE_BINARY:
            snprintf(optbuf, sizeof(optbuf), "%s=<binary>", opt->name);
            break;
        case AV_OPT_TYPE_CONST:
            snprintf(optbuf, sizeof(optbuf), "  [+-]%s", opt->name);
            break;
        default:
            snprintf(optbuf, sizeof(optbuf), "%s", opt->name);
            break;
        }
        optbuf[sizeof(optbuf) - 1] = 0;
        mp_info(log, "%-32s ", optbuf);
        if (opt->help)
            mp_info(log, " %s", opt->help);
        mp_info(log, "\n");
        if (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            encode_lavc_printoptions(log, obj, indent, subindent, opt->unit,
                                     filter_and, filter_eq);
    }
}