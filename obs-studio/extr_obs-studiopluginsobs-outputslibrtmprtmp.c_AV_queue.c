#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int av_len; int /*<<< orphan*/  av_val; } ;
struct TYPE_8__ {size_t av_len; char* av_val; } ;
struct TYPE_9__ {int num; TYPE_1__ name; } ;
typedef  TYPE_2__ RTMP_METHOD ;
typedef  TYPE_3__ AVal ;

/* Variables and functions */
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* realloc (TYPE_2__*,int) ; 

__attribute__((used)) static void
AV_queue(RTMP_METHOD **vals, int *num, AVal *av, int txn)
{
    char *tmp;
    if (!(*num & 0x0f))
        *vals = realloc(*vals, (*num + 16) * sizeof(RTMP_METHOD));
    tmp = malloc(av->av_len + 1);
    memcpy(tmp, av->av_val, av->av_len);
    tmp[av->av_len] = '\0';
    (*vals)[*num].num = txn;
    (*vals)[*num].name.av_len = av->av_len;
    (*vals)[(*num)++].name.av_val = tmp;
}