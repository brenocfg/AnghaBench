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
struct iucv_message {int flags; int* rmmsg; size_t length; } ;

/* Variables and functions */
 int IUCV_IPRMDATA ; 

__attribute__((used)) static inline size_t iucv_msg_length(struct iucv_message *msg)
{
	size_t datalen;

	if (msg->flags & IUCV_IPRMDATA) {
		datalen = 0xff - msg->rmmsg[7];
		return (datalen < 8) ? datalen : 8;
	}
	return msg->length;
}