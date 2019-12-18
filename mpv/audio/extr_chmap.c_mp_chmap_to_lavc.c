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
typedef  int /*<<< orphan*/  uint64_t ;
struct mp_chmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_chmap_is_lavc (struct mp_chmap const*) ; 
 int /*<<< orphan*/  mp_chmap_to_lavc_unchecked (struct mp_chmap const*) ; 

uint64_t mp_chmap_to_lavc(const struct mp_chmap *src)
{
    if (!mp_chmap_is_lavc(src))
        return 0;
    return mp_chmap_to_lavc_unchecked(src);
}