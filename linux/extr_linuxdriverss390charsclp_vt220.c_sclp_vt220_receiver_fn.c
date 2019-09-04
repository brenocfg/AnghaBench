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
struct evbuf_header {int length; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
#define  SCLP_VT220_SESSION_DATA 130 
#define  SCLP_VT220_SESSION_ENDED 129 
#define  SCLP_VT220_SESSION_STARTED 128 
 int /*<<< orphan*/  sclp_vt220_handle_input (char*,unsigned int) ; 
 int /*<<< orphan*/  sclp_vt220_port ; 
 int /*<<< orphan*/  sclp_vt220_reset_session () ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sclp_vt220_receiver_fn(struct evbuf_header *evbuf)
{
	char *buffer;
	unsigned int count;

	buffer = (char *) ((addr_t) evbuf + sizeof(struct evbuf_header));
	count = evbuf->length - sizeof(struct evbuf_header);

	switch (*buffer) {
	case SCLP_VT220_SESSION_ENDED:
	case SCLP_VT220_SESSION_STARTED:
		sclp_vt220_reset_session();
		break;
	case SCLP_VT220_SESSION_DATA:
		/* Send input to line discipline */
		buffer++;
		count--;
		sclp_vt220_handle_input(buffer, count);
		tty_flip_buffer_push(&sclp_vt220_port);
		break;
	}
}