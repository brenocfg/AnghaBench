#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_4__ {int len; scalar_t__ data; struct TYPE_4__* next; } ;
struct TYPE_3__ {scalar_t__ bytes_free; int /*<<< orphan*/  total_len; TYPE_2__* tail; int /*<<< orphan*/  num_chunks; } ;
typedef  int /*<<< orphan*/  StateFileChunk ;

/* Variables and functions */
 scalar_t__ MAXALIGN (scalar_t__) ; 
 scalar_t__ Max (scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,scalar_t__) ; 
 scalar_t__ palloc (scalar_t__) ; 
 TYPE_2__* palloc0 (int) ; 
 TYPE_1__ records ; 

__attribute__((used)) static void
save_state_data(const void *data, uint32 len)
{
	uint32		padlen = MAXALIGN(len);

	if (padlen > records.bytes_free)
	{
		records.tail->next = palloc0(sizeof(StateFileChunk));
		records.tail = records.tail->next;
		records.tail->len = 0;
		records.tail->next = NULL;
		records.num_chunks++;

		records.bytes_free = Max(padlen, 512);
		records.tail->data = palloc(records.bytes_free);
	}

	memcpy(((char *) records.tail->data) + records.tail->len, data, len);
	records.tail->len += padlen;
	records.bytes_free -= padlen;
	records.total_len += padlen;
}