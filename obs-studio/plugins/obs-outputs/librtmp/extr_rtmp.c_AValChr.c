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
struct TYPE_3__ {int av_len; char* av_val; } ;
typedef  TYPE_1__ AVal ;

/* Variables and functions */

__attribute__((used)) static char *AValChr(AVal *av, char c)
{
    int i;
    for (i = 0; i < av->av_len; i++)
    {
        if (av->av_val[i] == c)
            return &av->av_val[i];
    }
    return NULL;
}