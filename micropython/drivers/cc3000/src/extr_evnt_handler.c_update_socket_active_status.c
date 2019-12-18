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
typedef  scalar_t__ INT32 ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  BSD_RSP_PARAMS_SOCKET_OFFSET ; 
 int /*<<< orphan*/  BSD_RSP_PARAMS_STATUS_OFFSET ; 
 scalar_t__ ERROR_SOCKET_INACTIVE ; 
 int /*<<< orphan*/  SOCKET_STATUS_INACTIVE ; 
 int /*<<< orphan*/  STREAM_TO_UINT32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_socket_active_status (scalar_t__,int /*<<< orphan*/ ) ; 

void update_socket_active_status(CHAR *resp_params)
{
	INT32 status, sd;

	STREAM_TO_UINT32(resp_params, BSD_RSP_PARAMS_SOCKET_OFFSET,sd);
	STREAM_TO_UINT32(resp_params, BSD_RSP_PARAMS_STATUS_OFFSET,status);

	if(ERROR_SOCKET_INACTIVE == status)
	{
		set_socket_active_status(sd, SOCKET_STATUS_INACTIVE);
	}
}