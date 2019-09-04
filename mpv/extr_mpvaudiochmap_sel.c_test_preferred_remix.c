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
struct mp_chmap {int dummy; } ;

/* Variables and functions */
 int MP_ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 scalar_t__ mp_chmap_equals_reordered (struct mp_chmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_chmap_remove_na (struct mp_chmap*) ; 
 int /*<<< orphan*/ ** preferred_remix ; 

__attribute__((used)) static bool test_preferred_remix(const struct mp_chmap *src,
                                 const struct mp_chmap *dst)
{
    struct mp_chmap src_p = *src, dst_p = *dst;
    mp_chmap_remove_na(&src_p);
    mp_chmap_remove_na(&dst_p);
    for (int n = 0; n < MP_ARRAY_SIZE(preferred_remix); n++) {
        if (mp_chmap_equals_reordered(&src_p, &preferred_remix[n][0]) &&
            mp_chmap_equals_reordered(&dst_p, &preferred_remix[n][1]))
            return true;
    }
    return false;
}