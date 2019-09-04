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
typedef  int /*<<< orphan*/  uint8_t ;
struct obs_x264 {size_t sei_size; int /*<<< orphan*/ * sei; int /*<<< orphan*/  context; } ;

/* Variables and functions */

__attribute__((used)) static bool obs_x264_sei(void *data, uint8_t **sei, size_t *size)
{
	struct obs_x264 *obsx264 = data;

	if (!obsx264->context)
		return false;

	*sei  = obsx264->sei;
	*size = obsx264->sei_size;
	return true;
}