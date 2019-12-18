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
struct cmd_bind {int num_keys; int const* keys; } ;

/* Variables and functions */

__attribute__((used)) static bool bind_matches_key(struct cmd_bind *bind, int num_keys, const int *keys)
{
    if (bind->num_keys != num_keys)
        return false;
    for (int i = 0; i < num_keys; i++) {
        if (bind->keys[i] != keys[i])
            return false;
    }
    return true;
}