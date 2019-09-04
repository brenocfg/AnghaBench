#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ hCard; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 TYPE_1__ kuhl_m_acr_Comm ; 
 scalar_t__ kuhl_m_acr_hContext ; 

NTSTATUS kuhl_m_acr_init()
{
	kuhl_m_acr_hContext = 0;
	kuhl_m_acr_Comm.hCard = 0;
	return STATUS_SUCCESS;
}