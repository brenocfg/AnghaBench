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
 int /*<<< orphan*/  LSAPI_Inc_Req_Processed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_initial_start_reqs ; 
 int /*<<< orphan*/  s_requests_count ; 

__attribute__((used)) static void LSCRIU_Get_Global_Counter(void)
{
    if (!s_initial_start_reqs) {
        return;
    }
    s_requests_count = LSAPI_Inc_Req_Processed(0);

}