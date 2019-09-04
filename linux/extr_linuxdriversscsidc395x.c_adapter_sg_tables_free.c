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
struct AdapterCtlBlk {TYPE_1__* srb_array; } ;
struct TYPE_2__ {int /*<<< orphan*/  segment_x; } ;

/* Variables and functions */
 int DC395x_MAX_SRB_CNT ; 
 unsigned int PAGE_SIZE ; 
 unsigned int SEGMENTX_LEN ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adapter_sg_tables_free(struct AdapterCtlBlk *acb)
{
	int i;
	const unsigned srbs_per_page = PAGE_SIZE/SEGMENTX_LEN;

	for (i = 0; i < DC395x_MAX_SRB_CNT; i += srbs_per_page)
		kfree(acb->srb_array[i].segment_x);
}