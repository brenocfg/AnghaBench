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
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** uriencode_map ; 

bool uriencode(const char *src, char *dst, const size_t srclen, const size_t dstlen) {
    int x;
    size_t d = 0;
    for (x = 0; x < srclen; x++) {
        if (d + 4 > dstlen)
            return false;
        if (uriencode_map[(unsigned char) src[x]] != NULL) {
            memcpy(&dst[d], uriencode_map[(unsigned char) src[x]], 3);
            d += 3;
        } else {
            dst[d] = src[x];
            d++;
        }
    }
    dst[d] = '\0';
    return true;
}