#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mode; } ;
typedef  TYPE_1__ RAGraph ;

/* Variables and functions */
 scalar_t__ R_AGRAPH_MODE_SUMMARY ; 

__attribute__((used)) static bool is_summary(const RAGraph *g) {
	return g->mode == R_AGRAPH_MODE_SUMMARY;
}