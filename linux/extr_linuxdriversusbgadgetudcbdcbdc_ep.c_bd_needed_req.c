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
struct TYPE_2__ {int length; } ;
struct bdc_req {TYPE_1__ usb_req; } ;

/* Variables and functions */
 int BD_MAX_BUFF_SIZE ; 

__attribute__((used)) static inline int bd_needed_req(struct bdc_req *req)
{
	int bd_needed = 0;
	int remaining;

	/* 1 bd needed for 0 byte transfer */
	if (req->usb_req.length == 0)
		return 1;

	/* remaining bytes after tranfering all max BD size BD's */
	remaining = req->usb_req.length % BD_MAX_BUFF_SIZE;
	if (remaining)
		bd_needed++;

	/* How many maximum BUFF size BD's ? */
	remaining = req->usb_req.length / BD_MAX_BUFF_SIZE;
	bd_needed += remaining;

	return bd_needed;
}