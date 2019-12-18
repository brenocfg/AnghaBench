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
struct hook_handler {scalar_t__ priority; int seq; } ;

/* Variables and functions */

__attribute__((used)) static int compare_hook(const void *pa, const void *pb)
{
    struct hook_handler **h1 = (void *)pa;
    struct hook_handler **h2 = (void *)pb;
    if ((*h1)->priority != (*h2)->priority)
        return (*h1)->priority - (*h2)->priority;
    return (*h1)->seq - (*h2)->seq;
}