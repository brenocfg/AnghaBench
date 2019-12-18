#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ num; scalar_t__ den; } ;
typedef  TYPE_1__ AVRational ;

/* Variables and functions */
 TYPE_1__ AV_TIME_BASE_Q ; 

__attribute__((used)) static AVRational get_def_tb(AVRational *tb)
{
    return tb && tb->num > 0 && tb->den > 0 ? *tb : AV_TIME_BASE_Q;
}