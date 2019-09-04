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
struct TYPE_4__ {int offset; scalar_t__ type; scalar_t__ name; } ;
typedef  TYPE_1__ AVOption ;

/* Variables and functions */
 scalar_t__ AV_OPT_TYPE_CONST ; 
 TYPE_1__* av_opt_next (void*,TYPE_1__ const*) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static void resolve_positional_arg(void *avobj, char **name)
{
    if (!*name || (*name)[0] != '@' || !avobj)
        return;

    char *end = NULL;
    int pos = strtol(*name + 1, &end, 10);
    if (!end || *end)
        return;

    const AVOption *opt = NULL;
    int offset = -1;
    while (1) {
        opt = av_opt_next(avobj, opt);
        if (!opt)
            return;
        // This is what libavfilter's parser does to skip aliases.
        if (opt->offset != offset && opt->type != AV_OPT_TYPE_CONST)
            pos--;
        if (pos < 0) {
            *name = (char *)opt->name;
            return;
        }
        offset = opt->offset;
    }
}