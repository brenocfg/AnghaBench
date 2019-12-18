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
struct list_head {int /*<<< orphan*/  n; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_check_node (int /*<<< orphan*/ *,char const*) ; 

struct list_head *list_check(const struct list_head *h, const char *abortstr)
{
    if (!list_check_node(&h->n, abortstr))
        return NULL;
    return (struct list_head *)h;
}