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
typedef  int /*<<< orphan*/  shm_mq_handle ;
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DestRemote ; 
 int /*<<< orphan*/  FrontendProtocol ; 
 int /*<<< orphan*/  PG_PROTOCOL_LATEST ; 
 int /*<<< orphan*/ * PqCommMethods ; 
 int /*<<< orphan*/  PqCommMqMethods ; 
 int /*<<< orphan*/  on_dsm_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_cleanup_redirect_to_shm_mq ; 
 int /*<<< orphan*/ * pq_mq_handle ; 
 int /*<<< orphan*/  whereToSendOutput ; 

void
pq_redirect_to_shm_mq(dsm_segment *seg, shm_mq_handle *mqh)
{
	PqCommMethods = &PqCommMqMethods;
	pq_mq_handle = mqh;
	whereToSendOutput = DestRemote;
	FrontendProtocol = PG_PROTOCOL_LATEST;
	on_dsm_detach(seg, pq_cleanup_redirect_to_shm_mq, (Datum) 0);
}