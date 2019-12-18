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
typedef  int /*<<< orphan*/  PMIB_IPFORWARD_ROW2 ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteIpForwardEntry2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD
DeleteRoute(PMIB_IPFORWARD_ROW2 fwd_row)
{
    return DeleteIpForwardEntry2(fwd_row);
}