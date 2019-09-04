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
typedef  scalar_t__ u16 ;
typedef  unsigned int s16 ;

/* Variables and functions */
 int USB_MAX_FRAME_NUMBER ; 

__attribute__((used)) static inline s16
frame_diff(u16 left, u16 right)
{
	return ((unsigned) (left - right)) % (USB_MAX_FRAME_NUMBER + 1);
}