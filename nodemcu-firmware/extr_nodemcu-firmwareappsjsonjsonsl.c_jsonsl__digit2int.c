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

__attribute__((used)) static int
jsonsl__digit2int(char ch) {
    int d = ch - '0';
    if ((unsigned) d < 10) {
        return d;
    }
    d = ch - 'a';
    if ((unsigned) d < 6) {
        return d + 10;
    }
    d = ch - 'A';
    if ((unsigned) d < 6) {
        return d + 10;
    }
    return -1;
}