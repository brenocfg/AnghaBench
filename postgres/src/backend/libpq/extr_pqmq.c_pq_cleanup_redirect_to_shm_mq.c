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
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DestNone ; 
 int /*<<< orphan*/ * pq_mq_handle ; 
 int /*<<< orphan*/  whereToSendOutput ; 

__attribute__((used)) static void
pq_cleanup_redirect_to_shm_mq(dsm_segment *seg, Datum arg)
{
	pq_mq_handle = NULL;
	whereToSendOutput = DestNone;
}