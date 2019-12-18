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
struct hwdec_info {scalar_t__ auto_pos; scalar_t__ copying; scalar_t__ rank; } ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 

__attribute__((used)) static int hwdec_compare(const void *p1, const void *p2)
{
    struct hwdec_info *h1 = (void *)p1;
    struct hwdec_info *h2 = (void *)p2;

    if (h1 == h2)
        return 0;

    // Strictly put non-preferred hwdecs to the end of the list.
    if ((h1->auto_pos == INT_MAX) != (h2->auto_pos == INT_MAX))
        return h1->auto_pos == INT_MAX ? 1 : -1;
    // List non-copying entries first, so --hwdec=auto takes them.
    if (h1->copying != h2->copying)
        return h1->copying ? 1 : -1;
    // Order by autoprobe preferrence order.
    if (h1->auto_pos != h2->auto_pos)
        return h1->auto_pos > h2->auto_pos ? 1 : -1;
    // Fallback sort order to make sorting stable.
    return h1->rank > h2->rank ? 1 :-1;
}