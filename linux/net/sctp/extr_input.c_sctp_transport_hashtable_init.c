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

/* Variables and functions */
 int rhltable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_hash_params ; 
 int /*<<< orphan*/  sctp_transport_hashtable ; 

int sctp_transport_hashtable_init(void)
{
	return rhltable_init(&sctp_transport_hashtable, &sctp_hash_params);
}