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
typedef  int uint32_t ;

/* Variables and functions */
 int digits (int,int,int*,char**,int) ; 
 char* itoa (int,char*,int,int) ; 

char* itoa_u32(uint32_t u, char* p) {
    int d = 0,n;
         if (u >=100000000) n = digits(u, 100000000, &d, &p, 10);
    else if (u <       100) n = digits(u,         1, &d, &p,  2);
    else if (u <     10000) n = digits(u,       100, &d, &p,  4);
    else if (u <   1000000) n = digits(u,     10000, &d, &p,  6);
    else                    n = digits(u,   1000000, &d, &p,  8);
    return itoa( u, p, d, n );
}