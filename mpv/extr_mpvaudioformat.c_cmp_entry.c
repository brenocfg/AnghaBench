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
struct entry {scalar_t__ score; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_entry(const void *a, const void *b)
{
#define CMP_INT(a, b) (a > b ? 1 : (a < b ? -1 : 0))
    return -CMP_INT(((struct entry *)a)->score, ((struct entry *)b)->score);
}