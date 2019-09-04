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
struct sclp_buffer {unsigned short columns; unsigned short htab; scalar_t__ current_length; int /*<<< orphan*/ * current_line; scalar_t__ char_sum; scalar_t__ messages; scalar_t__ retry_count; struct sccb_header* sccb; } ;
struct sccb_header {int length; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  memset (struct sccb_header*,int /*<<< orphan*/ ,int) ; 

struct sclp_buffer *
sclp_make_buffer(void *page, unsigned short columns, unsigned short htab)
{
	struct sclp_buffer *buffer;
	struct sccb_header *sccb;

	sccb = (struct sccb_header *) page;
	/*
	 * We keep the struct sclp_buffer structure at the end
	 * of the sccb page.
	 */
	buffer = ((struct sclp_buffer *) ((addr_t) sccb + PAGE_SIZE)) - 1;
	buffer->sccb = sccb;
	buffer->retry_count = 0;
	buffer->messages = 0;
	buffer->char_sum = 0;
	buffer->current_line = NULL;
	buffer->current_length = 0;
	buffer->columns = columns;
	buffer->htab = htab;

	/* initialize sccb */
	memset(sccb, 0, sizeof(struct sccb_header));
	sccb->length = sizeof(struct sccb_header);

	return buffer;
}