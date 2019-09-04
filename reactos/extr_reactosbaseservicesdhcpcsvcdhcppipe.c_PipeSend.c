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
typedef  int DWORD ;
typedef  int /*<<< orphan*/  COMM_DHCP_REPLY ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CommPipe ; 
 scalar_t__ WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 

DWORD PipeSend( COMM_DHCP_REPLY *Reply ) {
    DWORD Written = 0;
    BOOL Success =
        WriteFile( CommPipe,
                   Reply,
                   sizeof(*Reply),
                   &Written,
                   NULL );
    return Success ? Written : -1;
}