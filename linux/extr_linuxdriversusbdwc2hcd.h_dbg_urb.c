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
struct urb {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 scalar_t__ PIPE_BULK ; 
 scalar_t__ PIPE_CONTROL ; 
 scalar_t__ usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool dbg_urb(struct urb *urb)
{
	return usb_pipetype(urb->pipe) == PIPE_BULK ||
	       usb_pipetype(urb->pipe) == PIPE_CONTROL;
}