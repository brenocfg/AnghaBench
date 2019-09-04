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
struct hpi_response_header {int dummy; } ;
struct hpi_response {int dummy; } ;
struct hpi_message_header {int dummy; } ;
struct hpi_message {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpi_send_recv (struct hpi_message*,struct hpi_response*) ; 

__attribute__((used)) static inline void hpi_send_recvV1(struct hpi_message_header *m,
	struct hpi_response_header *r)
{
	hpi_send_recv((struct hpi_message *)m, (struct hpi_response *)r);
}