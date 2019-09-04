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
struct urb {int /*<<< orphan*/ * setup_packet; } ;
struct mon_event_text {scalar_t__ xfertype; int /*<<< orphan*/  setup; } ;
struct mon_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETUP_MAX ; 
 scalar_t__ USB_ENDPOINT_XFER_CONTROL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char mon_text_get_setup(struct mon_event_text *ep,
    struct urb *urb, char ev_type, struct mon_bus *mbus)
{

	if (ep->xfertype != USB_ENDPOINT_XFER_CONTROL || ev_type != 'S')
		return '-';

	if (urb->setup_packet == NULL)
		return 'Z';	/* '0' would be not as pretty. */

	memcpy(ep->setup, urb->setup_packet, SETUP_MAX);
	return 0;
}