#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ AVInputFormat ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,char**,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* av_demuxer_iterate (void**) ; 
 int /*<<< orphan*/ * talloc_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

char **mp_get_lavf_demuxers(void)
{
    char **list = NULL;
    void *iter = NULL;
    int num = 0;
    for (;;) {
        const AVInputFormat *cur = av_demuxer_iterate(&iter);
        if (!cur)
            break;
        MP_TARRAY_APPEND(NULL, list, num, talloc_strdup(NULL, cur->name));
    }
    MP_TARRAY_APPEND(NULL, list, num, NULL);
    return list;
}