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
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kuhl_m_sekurlsa_nt6_KeyInit ; 
 int /*<<< orphan*/  kuhl_m_sekurlsa_nt6_LsaCleanupProtectedMemory () ; 

NTSTATUS kuhl_m_sekurlsa_nt6_clean()
{
	if(NT_SUCCESS(kuhl_m_sekurlsa_nt6_KeyInit))
		kuhl_m_sekurlsa_nt6_LsaCleanupProtectedMemory();
	return STATUS_SUCCESS;
}