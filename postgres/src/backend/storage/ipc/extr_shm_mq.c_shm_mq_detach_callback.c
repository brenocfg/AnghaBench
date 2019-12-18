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
typedef  int /*<<< orphan*/  shm_mq ;
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_mq_detach_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
shm_mq_detach_callback(dsm_segment *seg, Datum arg)
{
	shm_mq	   *mq = (shm_mq *) DatumGetPointer(arg);

	shm_mq_detach_internal(mq);
}