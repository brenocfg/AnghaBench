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
struct gb_operation_msg_hdr {int dummy; } ;
struct gb_host_device {size_t buffer_size_max; } ;
struct gb_connection {struct gb_host_device* hd; } ;

/* Variables and functions */

size_t gb_operation_get_payload_size_max(struct gb_connection *connection)
{
	struct gb_host_device *hd = connection->hd;

	return hd->buffer_size_max - sizeof(struct gb_operation_msg_hdr);
}