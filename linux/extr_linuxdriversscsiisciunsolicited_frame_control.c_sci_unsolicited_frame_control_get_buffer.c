#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_4__ {TYPE_1__* array; } ;
struct sci_unsolicited_frame_control {TYPE_2__ buffers; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;
struct TYPE_3__ {void* buffer; } ;

/* Variables and functions */
 int SCI_FAILURE_INVALID_PARAMETER_VALUE ; 
 int SCI_SUCCESS ; 
 size_t SCU_MAX_UNSOLICITED_FRAMES ; 

enum sci_status sci_unsolicited_frame_control_get_buffer(struct sci_unsolicited_frame_control *uf_control,
							 u32 frame_index,
							 void **frame_buffer)
{
	if (frame_index < SCU_MAX_UNSOLICITED_FRAMES) {
		*frame_buffer = uf_control->buffers.array[frame_index].buffer;

		return SCI_SUCCESS;
	}

	return SCI_FAILURE_INVALID_PARAMETER_VALUE;
}