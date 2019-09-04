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
typedef  int /*<<< orphan*/  u32 ;
struct sis_video_info {int dummy; } ;
struct TYPE_2__ {struct sis_video_info* vinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  sis_int_free (struct sis_video_info*,int /*<<< orphan*/ ) ; 
 TYPE_1__* sisfb_heap ; 

void
sis_free(u32 base)
{
	struct sis_video_info *ivideo = sisfb_heap->vinfo;

	sis_int_free(ivideo, base);
}