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
struct nvec_msg {int* data; } ;

/* Variables and functions */

__attribute__((used)) static bool nvec_msg_is_event(struct nvec_msg *msg)
{
	return msg->data[0] >> 7;
}