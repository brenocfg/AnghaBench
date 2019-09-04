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
typedef  int /*<<< orphan*/  u16 ;
struct hpi_response_header {int dummy; } ;
struct hpi_message_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpi_init_messageV1 (struct hpi_message_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_init_responseV1 (struct hpi_response_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hpi_init_message_responseV1(struct hpi_message_header *phm, u16 msg_size,
	struct hpi_response_header *phr, u16 res_size, u16 object,
	u16 function)
{
	hpi_init_messageV1(phm, msg_size, object, function);
	hpi_init_responseV1(phr, res_size, object, function);
}