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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PDCSHADOW_DOMAIN_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  kuhl_m_lsadump_dcshadow_bind_DRSR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcshadow_call_AddEntry_manual ; 

ULONG kuhl_m_lsadump_dcshadow_AddEntry(PDCSHADOW_DOMAIN_INFO info)
{
	return kuhl_m_lsadump_dcshadow_bind_DRSR(info, kuhl_m_lsadump_dcshadow_call_AddEntry_manual);
}