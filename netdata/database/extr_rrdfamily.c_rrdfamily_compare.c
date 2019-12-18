#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ hash_family; int /*<<< orphan*/  family; } ;
typedef  TYPE_1__ RRDFAMILY ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rrdfamily_compare(void *a, void *b) {
    if(((RRDFAMILY *)a)->hash_family < ((RRDFAMILY *)b)->hash_family) return -1;
    else if(((RRDFAMILY *)a)->hash_family > ((RRDFAMILY *)b)->hash_family) return 1;
    else return strcmp(((RRDFAMILY *)a)->family, ((RRDFAMILY *)b)->family);
}