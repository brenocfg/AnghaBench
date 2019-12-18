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
typedef  int /*<<< orphan*/  ret ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  Tg ;
typedef  int /*<<< orphan*/  PKULL_M_PN532_COMM ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  PN532_CMD_InRelease ; 
 scalar_t__ kull_m_pn532_sendrecv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int*) ; 

BOOL kull_m_pn532_InRelease(PKULL_M_PN532_COMM comm, const BYTE Tg)
{
	BOOL status = FALSE;
	BYTE ret;
	UINT16 wOut = sizeof(ret);
	if(kull_m_pn532_sendrecv(comm, PN532_CMD_InRelease, &Tg, sizeof(Tg), &ret, &wOut))
		status = !ret;
	return status;
}