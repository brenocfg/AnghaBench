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

/* Variables and functions */
#define  PIPE_BULK 135 
#define  PIPE_CONTROL 134 
#define  PIPE_INTERRUPT 133 
#define  PIPE_ISOCHRONOUS 132 
#define  QH_INFO1_TR_TYPE_BULK 131 
#define  QH_INFO1_TR_TYPE_CTRL 130 
#define  QH_INFO1_TR_TYPE_INT 129 
#define  QH_INFO1_TR_TYPE_ISOC 128 
 size_t usb_pipetype (unsigned int) ; 

__attribute__((used)) static inline unsigned usb_pipe_to_qh_type(unsigned pipe)
{
	static const unsigned type[] = {
		[PIPE_ISOCHRONOUS] = QH_INFO1_TR_TYPE_ISOC,
		[PIPE_INTERRUPT]   = QH_INFO1_TR_TYPE_INT,
		[PIPE_CONTROL]     = QH_INFO1_TR_TYPE_CTRL,
		[PIPE_BULK]        = QH_INFO1_TR_TYPE_BULK,
	};
	return type[usb_pipetype(pipe)];
}