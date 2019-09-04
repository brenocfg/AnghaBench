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
typedef  void* u32 ;
struct calling_interface_buffer {void** input; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct calling_interface_buffer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dell_fill_request(struct calling_interface_buffer *buffer,
			       u32 arg0, u32 arg1, u32 arg2, u32 arg3)
{
	memset(buffer, 0, sizeof(struct calling_interface_buffer));
	buffer->input[0] = arg0;
	buffer->input[1] = arg1;
	buffer->input[2] = arg2;
	buffer->input[3] = arg3;
}