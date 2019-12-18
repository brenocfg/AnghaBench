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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  kuhl_m_process_list_callback_process ; 
 int /*<<< orphan*/  kull_m_process_getProcessInformation (int /*<<< orphan*/ ,int*) ; 

NTSTATUS kuhl_m_process_list(int argc, wchar_t * argv[])
{
	return kull_m_process_getProcessInformation(kuhl_m_process_list_callback_process, &argc);
}