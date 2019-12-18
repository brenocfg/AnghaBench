#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ead_msg_number {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {void* len; void* type; } ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 TYPE_1__* A ; 
 struct ead_msg_number* EAD_DATA (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ EAD_TYPE_SEND_A ; 
 int /*<<< orphan*/  EAD_TYPE_SEND_B ; 
 int /*<<< orphan*/  handle_b ; 
 void* htonl (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* msg ; 
 int /*<<< orphan*/  number ; 
 int send_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* t_clientgenexp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc ; 

__attribute__((used)) static int
send_a(void)
{
	struct ead_msg_number *num = EAD_DATA(msg, number);
	A = t_clientgenexp(tc);
	msg->type = htonl(EAD_TYPE_SEND_A);
	msg->len = htonl(sizeof(struct ead_msg_number) + A->len);
	memcpy(num->data, A->data, A->len);
	return send_packet(EAD_TYPE_SEND_B, handle_b, 1);
}