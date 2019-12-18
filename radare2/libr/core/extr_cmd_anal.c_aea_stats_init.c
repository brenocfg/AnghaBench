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
struct TYPE_3__ {void* inputregs; void* regwrite; void* regread; void* regs; } ;
typedef  TYPE_1__ AeaStats ;

/* Variables and functions */
 int /*<<< orphan*/  free ; 
 void* r_list_newf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aea_stats_init (AeaStats *stats) {
	stats->regs = r_list_newf (free);
	stats->regread = r_list_newf (free);
	stats->regwrite = r_list_newf (free);
	stats->inputregs = r_list_newf (free);
}