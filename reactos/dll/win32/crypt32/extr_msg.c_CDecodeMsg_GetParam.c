#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* pbData; int cbData; } ;
struct TYPE_9__ {int type; int /*<<< orphan*/  properties; } ;
typedef  TYPE_1__* HCRYPTMSG ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ CRYPT_DATA_BLOB ;
typedef  TYPE_1__ CDecodeMsg ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CDecodeEnvelopedMsg_GetParam (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CDecodeHashMsg_GetParam (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CDecodeSignedMsg_GetParam (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
#define  CMSG_ENVELOPED 131 
#define  CMSG_HASHED 130 
#define  CMSG_SIGNED 129 
#define  CMSG_TYPE_PARAM 128 
 int /*<<< orphan*/  CRYPT_CopyParam (void*,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  CRYPT_E_INVALID_MSG_TYPE ; 
 int /*<<< orphan*/  ContextPropertyList_FindProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL CDecodeMsg_GetParam(HCRYPTMSG hCryptMsg, DWORD dwParamType,
 DWORD dwIndex, void *pvData, DWORD *pcbData)
{
    CDecodeMsg *msg = hCryptMsg;
    BOOL ret = FALSE;

    switch (msg->type)
    {
    case CMSG_HASHED:
        ret = CDecodeHashMsg_GetParam(msg, dwParamType, dwIndex, pvData,
         pcbData);
        break;
    case CMSG_ENVELOPED:
        ret = CDecodeEnvelopedMsg_GetParam(msg, dwParamType, dwIndex, pvData,
         pcbData);
        break;
    case CMSG_SIGNED:
        ret = CDecodeSignedMsg_GetParam(msg, dwParamType, dwIndex, pvData,
         pcbData);
        break;
    default:
        switch (dwParamType)
        {
        case CMSG_TYPE_PARAM:
            ret = CRYPT_CopyParam(pvData, pcbData, &msg->type,
             sizeof(msg->type));
            break;
        default:
        {
            CRYPT_DATA_BLOB blob;

            ret = ContextPropertyList_FindProperty(msg->properties, dwParamType,
             &blob);
            if (ret)
                ret = CRYPT_CopyParam(pvData, pcbData, blob.pbData,
                 blob.cbData);
            else
                SetLastError(CRYPT_E_INVALID_MSG_TYPE);
        }
        }
    }
    return ret;
}