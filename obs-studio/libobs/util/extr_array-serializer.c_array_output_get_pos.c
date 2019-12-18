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
struct TYPE_2__ {int /*<<< orphan*/  num; } ;
struct array_output_data {TYPE_1__ bytes; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */

__attribute__((used)) static int64_t array_output_get_pos(void *param)
{
	struct array_output_data *data = param;
	return (int64_t)data->bytes.num;
}