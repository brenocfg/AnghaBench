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
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PspCreateThreadNotifyRoutine ; 
 int /*<<< orphan*/  PspCreateThreadNotifyRoutineMax ; 
 int /*<<< orphan*/  ThreadReferences ; 
 int /*<<< orphan*/  kkll_m_notify_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

NTSTATUS kkll_m_notify_list_thread(PKIWI_BUFFER outBuffer)
{
	return kkll_m_notify_list(outBuffer, ThreadReferences, ARRAYSIZE(ThreadReferences), (PUCHAR *) &PspCreateThreadNotifyRoutine, &PspCreateThreadNotifyRoutineMax);
}