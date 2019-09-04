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
 char* netdata_map_chart_ids ; 

void netdata_fix_chart_id(char *s) {
    while ((*s = netdata_map_chart_ids[(unsigned char) *s])) s++;
}