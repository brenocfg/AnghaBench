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
typedef  size_t uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  print_string (char*) ; 
 size_t strlen (char const*) ; 

void print_box_string(const char text[]) {
    size_t len = strlen(text);
    char   out[len * 3 + 8];
    out[0] = 0xDA;
    for (uint8_t i = 0; i < len; i++) {
        out[i + 1] = 0xC4;
    }
    out[len + 1] = 0xBF;
    out[len + 2] = '\n';

    out[len + 3] = 0xB3;
    for (uint8_t i = 0; i < len; i++) {
        out[len + 4 + i] = text[i];
    }
    out[len * 2 + 4] = 0xB3;
    out[len * 2 + 5] = '\n';

    out[len * 2 + 6] = 0xC0;
    for (uint8_t i = 0; i < len; i++) {
        out[len * 2 + 7 + i] = 0xC4;
    }
    out[len * 3 + 7] = 0xD9;
    out[len * 3 + 8] = '\n';

    print_string(out);
}