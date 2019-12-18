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

/* Variables and functions */

__attribute__((used)) static inline int hash_int_key_cmp(const void *k1, const void *k2)
{
    intptr_t a = (intptr_t)k1;
    intptr_t b = (intptr_t)k2;

    return (a > b) - (a < b);
}