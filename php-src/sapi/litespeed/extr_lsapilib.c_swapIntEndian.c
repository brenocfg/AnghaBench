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

__attribute__((used)) static inline void swapIntEndian( int * pInteger )
{
    char * p = (char *)pInteger;
    register char b;
    b = p[0];
    p[0] = p[3];
    p[3] = b;
    b = p[1];
    p[1] = p[2];
    p[2] = b;

}