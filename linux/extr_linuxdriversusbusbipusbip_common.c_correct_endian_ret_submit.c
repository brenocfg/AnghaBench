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
struct usbip_header_ret_submit {int /*<<< orphan*/  error_count; int /*<<< orphan*/  number_of_packets; int /*<<< orphan*/  start_frame; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32s (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void correct_endian_ret_submit(struct usbip_header_ret_submit *pdu,
				      int send)
{
	if (send) {
		cpu_to_be32s(&pdu->status);
		cpu_to_be32s(&pdu->actual_length);
		cpu_to_be32s(&pdu->start_frame);
		cpu_to_be32s(&pdu->number_of_packets);
		cpu_to_be32s(&pdu->error_count);
	} else {
		be32_to_cpus(&pdu->status);
		be32_to_cpus(&pdu->actual_length);
		be32_to_cpus(&pdu->start_frame);
		be32_to_cpus(&pdu->number_of_packets);
		be32_to_cpus(&pdu->error_count);
	}
}