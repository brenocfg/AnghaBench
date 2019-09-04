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
struct scsi_target {int dummy; } ;
struct esp_target_data {scalar_t__ nego_goal_width; struct scsi_target* starget; } ;

/* Variables and functions */
 scalar_t__ spi_width (struct scsi_target*) ; 

__attribute__((used)) static int esp_need_to_nego_wide(struct esp_target_data *tp)
{
	struct scsi_target *target = tp->starget;

	return spi_width(target) != tp->nego_goal_width;
}