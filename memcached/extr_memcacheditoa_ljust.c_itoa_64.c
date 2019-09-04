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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 char* itoa_u64 (scalar_t__,char*) ; 

char* itoa_64(int64_t i, char* p) {
    uint64_t u = i;
    if (i < 0) {
        *p++ = '-';
        u = -u;
    }
    return itoa_u64(u, p);
}