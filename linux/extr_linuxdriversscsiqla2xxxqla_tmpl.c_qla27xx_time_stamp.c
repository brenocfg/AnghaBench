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
struct qla27xx_fwdt_template {int /*<<< orphan*/  capture_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void
qla27xx_time_stamp(struct qla27xx_fwdt_template *tmp)
{
	tmp->capture_timestamp = jiffies;
}