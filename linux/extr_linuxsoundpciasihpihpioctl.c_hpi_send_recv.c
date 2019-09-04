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
struct hpi_response {int dummy; } ;
struct hpi_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOWNER_KERNEL ; 
 int /*<<< orphan*/  hpi_send_recv_f (struct hpi_message*,struct hpi_response*,int /*<<< orphan*/ ) ; 

void hpi_send_recv(struct hpi_message *phm, struct hpi_response *phr)
{
	hpi_send_recv_f(phm, phr, HOWNER_KERNEL);
}