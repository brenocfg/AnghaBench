#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ av_len; int /*<<< orphan*/ * av_val; } ;
struct TYPE_5__ {scalar_t__ num; TYPE_1__ name; } ;
typedef  TYPE_2__ RTMP_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
AV_erase(RTMP_METHOD *vals, int *num, int i, int freeit)
{
    if (freeit)
        free(vals[i].name.av_val);
    (*num)--;
    for (; i < *num; i++)
    {
        vals[i] = vals[i + 1];
    }
    vals[i].name.av_val = NULL;
    vals[i].name.av_len = 0;
    vals[i].num = 0;
}