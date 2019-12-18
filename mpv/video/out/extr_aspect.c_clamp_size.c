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
 int MPMAX (int /*<<< orphan*/ ,int) ; 
 int MPMIN (int,int) ; 

__attribute__((used)) static void clamp_size(int size, int *start, int *end)
{
    *start = MPMAX(0, *start);
    *end = MPMIN(size, *end);
    if (*start >= *end) {
        *start = 0;
        *end = 1;
    }
}