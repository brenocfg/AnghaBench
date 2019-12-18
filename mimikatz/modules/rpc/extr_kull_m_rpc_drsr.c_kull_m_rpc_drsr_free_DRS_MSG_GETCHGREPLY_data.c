#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  V6; } ;
typedef  int DWORD ;
typedef  TYPE_1__ DRS_MSG_GETCHGREPLY ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  kull_m_rpc_ms_drsr_FreeDRS_MSG_GETCHGREPLY_V6 (int /*<<< orphan*/ *) ; 

void kull_m_rpc_drsr_free_DRS_MSG_GETCHGREPLY_data(DWORD dwOutVersion, DRS_MSG_GETCHGREPLY * reply)
{
	if(reply)
	{
		switch(dwOutVersion)
		{
		case 6:
			kull_m_rpc_ms_drsr_FreeDRS_MSG_GETCHGREPLY_V6(&reply->V6);
			break;
		case 1:
		case 2:
		case 7:
		case 9:
			PRINT_ERROR(L"TODO (maybe?)\n");
			break;
		default:
			PRINT_ERROR(L"dwOutVersion not valid (0x%08x - %u)\n", dwOutVersion, dwOutVersion);
			break;
		}
	}
}