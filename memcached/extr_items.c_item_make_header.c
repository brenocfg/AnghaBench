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
typedef  int /*<<< orphan*/  item ;
typedef  int /*<<< orphan*/  flags ;

/* Variables and functions */

__attribute__((used)) static size_t item_make_header(const uint8_t nkey, const unsigned int flags, const int nbytes,
                     char *suffix, uint8_t *nsuffix) {
    if (flags == 0) {
        *nsuffix = 0;
    } else {
        *nsuffix = sizeof(flags);
    }
    return sizeof(item) + nkey + *nsuffix + nbytes;
}