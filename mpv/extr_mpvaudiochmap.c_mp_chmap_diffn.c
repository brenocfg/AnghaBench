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
typedef  int uint64_t ;
struct mp_chmap {int dummy; } ;

/* Variables and functions */
 int av_popcount64 (int) ; 
 int mp_chmap_to_lavc_unchecked (struct mp_chmap const*) ; 

int mp_chmap_diffn(const struct mp_chmap *a, const struct mp_chmap *b)
{
    uint64_t a_mask = mp_chmap_to_lavc_unchecked(a);
    uint64_t b_mask = mp_chmap_to_lavc_unchecked(b);
    return av_popcount64((a_mask ^ b_mask) & a_mask);
}