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
 int /*<<< orphan*/  ets_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lwIPThreadFlag ; 
 int /*<<< orphan*/  lwIPThreadPrio ; 
 int /*<<< orphan*/  lwIPThreadQueue ; 
 int /*<<< orphan*/  lwIPThreadQueueLen ; 
 int /*<<< orphan*/  mbedtls_thread ; 

__attribute__((used)) static void mbedtls_threadinit(void)
{
	ets_task(mbedtls_thread, lwIPThreadPrio, lwIPThreadQueue, lwIPThreadQueueLen);
	lwIPThreadFlag = true;
}