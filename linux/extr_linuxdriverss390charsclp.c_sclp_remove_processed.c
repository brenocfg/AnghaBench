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
typedef  scalar_t__ u16 ;
struct sccb_header {scalar_t__ length; } ;
struct evbuf_header {scalar_t__ length; int flags; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct evbuf_header*,void*,scalar_t__) ; 

int
sclp_remove_processed(struct sccb_header *sccb)
{
	struct evbuf_header *evbuf;
	int unprocessed;
	u16 remaining;

	evbuf = (struct evbuf_header *) (sccb + 1);
	unprocessed = 0;
	remaining = sccb->length - sizeof(struct sccb_header);
	while (remaining > 0) {
		remaining -= evbuf->length;
		if (evbuf->flags & 0x80) {
			sccb->length -= evbuf->length;
			memcpy(evbuf, (void *) ((addr_t) evbuf + evbuf->length),
			       remaining);
		} else {
			unprocessed++;
			evbuf = (struct evbuf_header *)
					((addr_t) evbuf + evbuf->length);
		}
	}
	return unprocessed;
}