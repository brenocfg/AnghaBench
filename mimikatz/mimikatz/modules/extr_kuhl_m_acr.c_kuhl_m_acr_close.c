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
 int /*<<< orphan*/  SCardReleaseContext (scalar_t__) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kuhl_m_acr_Comm ; 
 scalar_t__ kuhl_m_acr_hContext ; 
 int /*<<< orphan*/  kull_m_acr_finish (int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_acr_close(int argc, wchar_t * argv[])
{
	kull_m_acr_finish(&kuhl_m_acr_Comm);
	if(kuhl_m_acr_hContext)
	{
		SCardReleaseContext(kuhl_m_acr_hContext);
		kuhl_m_acr_hContext = 0;
	}
	return STATUS_SUCCESS;
}