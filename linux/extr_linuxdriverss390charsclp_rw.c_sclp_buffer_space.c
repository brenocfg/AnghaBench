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
struct sclp_buffer {scalar_t__ current_length; int /*<<< orphan*/ * current_line; struct sccb_header* sccb; } ;
struct sccb_header {int length; } ;
struct msg_buf {int dummy; } ;

/* Variables and functions */
 int MAX_SCCB_ROOM ; 

int
sclp_buffer_space(struct sclp_buffer *buffer)
{
	struct sccb_header *sccb;
	int count;

	sccb = buffer->sccb;
	count = MAX_SCCB_ROOM - sccb->length;
	if (buffer->current_line != NULL)
		count -= sizeof(struct msg_buf) + buffer->current_length;
	return count;
}