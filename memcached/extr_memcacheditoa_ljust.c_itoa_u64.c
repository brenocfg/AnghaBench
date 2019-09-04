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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 char* itoa (int,char*,int,int) ; 
 char* itoa_u32 (int,char*) ; 
 char* out1 (int,char*) ; 

char* itoa_u64(uint64_t u, char* p) {
    int d;

    uint32_t lower = (uint32_t)u;
    if (lower == u) return itoa_u32(lower, p);

    uint64_t upper = u / 1000000000;
    p = itoa_u64(upper, p);
    lower = u - (upper * 1000000000);
    d = lower / 100000000;
    p = out1('0'+d,p);
    return itoa( lower, p, d, 9 );
}