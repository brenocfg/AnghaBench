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
struct TYPE_3__ {char** protocols; } ;
typedef  TYPE_1__ stream_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (int /*<<< orphan*/ *,char**,int,int /*<<< orphan*/ *) ; 
 TYPE_1__** stream_list ; 
 int /*<<< orphan*/ * talloc_strdup (int /*<<< orphan*/ *,char*) ; 

char **stream_get_proto_list(void)
{
    char **list = NULL;
    int num = 0;
    for (int i = 0; stream_list[i]; i++) {
        const stream_info_t *stream_info = stream_list[i];

        if (!stream_info->protocols)
            continue;

        for (int j = 0; stream_info->protocols[j]; j++) {
            if (*stream_info->protocols[j] == '\0')
               continue;

            MP_TARRAY_APPEND(NULL, list, num,
                                talloc_strdup(NULL, stream_info->protocols[j]));
        }
    }
    MP_TARRAY_APPEND(NULL, list, num, NULL);
    return list;
}