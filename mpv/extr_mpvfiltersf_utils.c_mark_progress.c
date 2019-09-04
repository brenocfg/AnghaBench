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
struct mp_subfilter {int /*<<< orphan*/  in; } ;
struct mp_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_filter_internal_mark_progress (struct mp_filter*) ; 
 struct mp_filter* mp_pin_get_manual_connection (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mark_progress(struct mp_subfilter *sub)
{
    // f == NULL is not really allowed, but at least don't crash.
    struct mp_filter *f = mp_pin_get_manual_connection(sub->in);
    if (f)
        mp_filter_internal_mark_progress(f);
}