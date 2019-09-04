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
struct TYPE_2__ {scalar_t__ hash; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ NAME_VALUE ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int name_value_compare(void* a, void* b) {
    if(((NAME_VALUE *)a)->hash < ((NAME_VALUE *)b)->hash) return -1;
    else if(((NAME_VALUE *)a)->hash > ((NAME_VALUE *)b)->hash) return 1;
    else return strcmp(((NAME_VALUE *)a)->name, ((NAME_VALUE *)b)->name);
}