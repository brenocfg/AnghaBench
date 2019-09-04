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
struct dummy_hcd {int* num_stream; } ;

/* Variables and functions */
 size_t usb_pipeendpoint (unsigned int) ; 
 scalar_t__ usb_pipeout (unsigned int) ; 

__attribute__((used)) static int get_max_streams_for_pipe(struct dummy_hcd *dum_hcd,
		unsigned int pipe)
{
	int max_streams;

	max_streams = dum_hcd->num_stream[usb_pipeendpoint(pipe)];
	if (usb_pipeout(pipe))
		max_streams >>= 4;
	else
		max_streams &= 0xf;
	max_streams++;
	return max_streams;
}