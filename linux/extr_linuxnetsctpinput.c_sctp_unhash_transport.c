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
struct sctp_transport {int /*<<< orphan*/  node; TYPE_1__* asoc; } ;
struct TYPE_2__ {scalar_t__ temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  rhltable_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_hash_params ; 
 int /*<<< orphan*/  sctp_transport_hashtable ; 

void sctp_unhash_transport(struct sctp_transport *t)
{
	if (t->asoc->temp)
		return;

	rhltable_remove(&sctp_transport_hashtable, &t->node,
			sctp_hash_params);
}