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
struct sctp_transport {int dummy; } ;
struct rhashtable_iter {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct sctp_transport*) ; 
 struct sctp_transport* SEQ_START_TOKEN ; 
 struct sctp_transport* sctp_transport_get_next (struct net*,struct rhashtable_iter*) ; 
 int /*<<< orphan*/  sctp_transport_put (struct sctp_transport*) ; 

struct sctp_transport *sctp_transport_get_idx(struct net *net,
					      struct rhashtable_iter *iter,
					      int pos)
{
	struct sctp_transport *t;

	if (!pos)
		return SEQ_START_TOKEN;

	while ((t = sctp_transport_get_next(net, iter)) && !IS_ERR(t)) {
		if (!--pos)
			break;
		sctp_transport_put(t);
	}

	return t;
}