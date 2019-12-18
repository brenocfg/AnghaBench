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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  kernel_uint_t ;

/* Variables and functions */
 int /*<<< orphan*/  str2kernel_uint_t (char const*) ; 

inline void arl_callback_str2kernel_uint_t(const char *name, uint32_t hash, const char *value, void *dst) {
    (void)name;
    (void)hash;

    register kernel_uint_t *d = dst;
    *d = str2kernel_uint_t(value);
    // fprintf(stderr, "name '%s' with hash %u and value '%s' is %llu\n", name, hash, value, (unsigned long long)*d);
}