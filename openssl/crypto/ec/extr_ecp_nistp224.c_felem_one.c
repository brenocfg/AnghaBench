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
typedef  int* felem ;

/* Variables and functions */

__attribute__((used)) static void felem_one(felem out)
{
    out[0] = 1;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
}