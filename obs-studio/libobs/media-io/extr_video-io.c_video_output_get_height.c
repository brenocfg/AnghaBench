#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  height; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
typedef  TYPE_2__ video_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

uint32_t video_output_get_height(const video_t *video)
{
	return video ? video->info.height : 0;
}