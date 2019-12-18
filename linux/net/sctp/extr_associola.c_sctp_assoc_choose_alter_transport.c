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
struct sctp_transport {int dummy; } ;
struct TYPE_2__ {struct sctp_transport* retran_path; struct sctp_transport* active_path; } ;
struct sctp_association {TYPE_1__ peer; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_assoc_update_retran_path (struct sctp_association*) ; 

struct sctp_transport *
sctp_assoc_choose_alter_transport(struct sctp_association *asoc,
				  struct sctp_transport *last_sent_to)
{
	/* If this is the first time packet is sent, use the active path,
	 * else use the retran path. If the last packet was sent over the
	 * retran path, update the retran path and use it.
	 */
	if (last_sent_to == NULL) {
		return asoc->peer.active_path;
	} else {
		if (last_sent_to == asoc->peer.retran_path)
			sctp_assoc_update_retran_path(asoc);

		return asoc->peer.retran_path;
	}
}