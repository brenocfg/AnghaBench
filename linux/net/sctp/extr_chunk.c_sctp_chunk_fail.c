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
struct sctp_chunk {TYPE_1__* msg; } ;
struct TYPE_2__ {int send_failed; int send_error; } ;

/* Variables and functions */

void sctp_chunk_fail(struct sctp_chunk *chunk, int error)
{
	chunk->msg->send_failed = 1;
	chunk->msg->send_error = error;
}