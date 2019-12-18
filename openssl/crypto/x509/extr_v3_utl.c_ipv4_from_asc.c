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
 int sscanf (char const*,char*,int*,int*,int*,int*) ; 

__attribute__((used)) static int ipv4_from_asc(unsigned char *v4, const char *in)
{
    int a0, a1, a2, a3;
    if (sscanf(in, "%d.%d.%d.%d", &a0, &a1, &a2, &a3) != 4)
        return 0;
    if ((a0 < 0) || (a0 > 255) || (a1 < 0) || (a1 > 255)
        || (a2 < 0) || (a2 > 255) || (a3 < 0) || (a3 > 255))
        return 0;
    v4[0] = a0;
    v4[1] = a1;
    v4[2] = a2;
    v4[3] = a3;
    return 1;
}