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

__attribute__((used)) static unsigned
id_already_exists(const size_t *ids, unsigned count, size_t new_id)
{
    unsigned i;

    for (i=0; i<count; i++) {
        if (ids[i] == new_id)
            return 1;
    }
    return 0;
}