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
struct ra_native_resource {char const* name; void* data; } ;
struct ra {int /*<<< orphan*/  num_native_resources; int /*<<< orphan*/  native_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct ra*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ra_native_resource) ; 

void ra_add_native_resource(struct ra *ra, const char *name, void *data)
{
    struct ra_native_resource r = {
        .name = name,
        .data = data,
    };
    MP_TARRAY_APPEND(ra, ra->native_resources, ra->num_native_resources, r);
}