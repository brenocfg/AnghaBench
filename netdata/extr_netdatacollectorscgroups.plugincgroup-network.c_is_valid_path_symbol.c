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

int is_valid_path_symbol(char c) {
    switch(c) {
        case '/':   // path separators
        case '\\':  // needed for virsh domains \x2d1\x2dname
        case ' ':   // space
        case '-':   // hyphen
        case '_':   // underscore
        case '.':   // dot
        case ',':   // comma
            return 1;

        default:
            return 0;
    }
}