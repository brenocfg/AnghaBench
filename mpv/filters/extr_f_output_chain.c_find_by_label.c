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
struct mp_user_filter {scalar_t__ label; } ;
struct chain {int num_user_filters; struct mp_user_filter** user_filters; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static struct mp_user_filter *find_by_label(struct chain *p, const char *label)
{
    for (int n = 0; n < p->num_user_filters; n++) {
        struct mp_user_filter *u = p->user_filters[n];
        if (label && u->label && strcmp(label, u->label) == 0)
            return u;
    }
    return NULL;
}