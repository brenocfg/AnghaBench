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
typedef  scalar_t__ SignOrVerify ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CSignedMsgData ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CSignedMsgData_Sign (int /*<<< orphan*/ *) ; 
 scalar_t__ CSignedMsgData_UpdateAuthenticatedAttributes (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ CSignedMsgData_UpdateHash (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ Sign ; 

__attribute__((used)) static BOOL CSignedMsgData_Update(CSignedMsgData *msg_data,
 const BYTE *pbData, DWORD cbData, BOOL fFinal, SignOrVerify flag)
{
    BOOL ret = CSignedMsgData_UpdateHash(msg_data, pbData, cbData);

    if (ret && fFinal)
    {
        ret = CSignedMsgData_UpdateAuthenticatedAttributes(msg_data, flag);
        if (ret && flag == Sign)
            ret = CSignedMsgData_Sign(msg_data);
    }
    return ret;
}