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

void remove_option(int opt_index, int *argc, char **argv) {
    int i;

    // remove the options.
    do {
        *argc = *argc - 1;
        for(i = opt_index; i < *argc; i++) {
            argv[i] = argv[i+1];
        }
        i = opt_index;
    } while(argv[i][0] != '-' && opt_index >= *argc);
}