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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {size_t num; int /*<<< orphan*/ * array; } ;
struct vt_h264_encoder {TYPE_1__ extra_data; } ;

/* Variables and functions */

__attribute__((used)) static bool vt_h264_extra_data(void *data, uint8_t **extra_data, size_t *size)
{
	struct vt_h264_encoder *enc = (struct vt_h264_encoder *)data;
	*extra_data = enc->extra_data.array;
	*size = enc->extra_data.num;
	return true;
}