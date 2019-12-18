#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  info; } ;
struct TYPE_16__ {int /*<<< orphan*/  pbData; } ;
struct TYPE_15__ {int /*<<< orphan*/  pbData; } ;
struct TYPE_12__ {int /*<<< orphan*/  pbData; } ;
struct TYPE_13__ {TYPE_2__ content; int /*<<< orphan*/  data; scalar_t__ crypt_prov; } ;
struct TYPE_14__ {TYPE_9__ signed_data; TYPE_3__ enveloped_data; int /*<<< orphan*/  hash; } ;
struct TYPE_11__ {int open_flags; } ;
struct TYPE_17__ {int type; int /*<<< orphan*/  properties; TYPE_6__ detached_data; TYPE_5__ msg_data; TYPE_4__ u; scalar_t__ crypt_prov; TYPE_1__ base; } ;
typedef  TYPE_7__* HCRYPTMSG ;
typedef  TYPE_7__ CDecodeMsg ;

/* Variables and functions */
 int CMSG_CRYPT_RELEASE_CONTEXT_FLAG ; 
#define  CMSG_ENVELOPED 130 
#define  CMSG_HASHED 129 
#define  CMSG_SIGNED 128 
 int /*<<< orphan*/  CSignedMsgData_CloseHandles (TYPE_9__*) ; 
 int /*<<< orphan*/  ContextPropertyList_Free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptDestroyHash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptReleaseContext (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CDecodeMsg_Close(HCRYPTMSG hCryptMsg)
{
    CDecodeMsg *msg = hCryptMsg;

    if (msg->crypt_prov && msg->base.open_flags & CMSG_CRYPT_RELEASE_CONTEXT_FLAG)
        CryptReleaseContext(msg->crypt_prov, 0);
    switch (msg->type)
    {
    case CMSG_HASHED:
        if (msg->u.hash)
            CryptDestroyHash(msg->u.hash);
        break;
    case CMSG_ENVELOPED:
        if (msg->u.enveloped_data.crypt_prov)
            CryptReleaseContext(msg->u.enveloped_data.crypt_prov, 0);
        LocalFree(msg->u.enveloped_data.data);
        CryptMemFree(msg->u.enveloped_data.content.pbData);
        break;
    case CMSG_SIGNED:
        if (msg->u.signed_data.info)
        {
            LocalFree(msg->u.signed_data.info);
            CSignedMsgData_CloseHandles(&msg->u.signed_data);
        }
        break;
    }
    CryptMemFree(msg->msg_data.pbData);
    CryptMemFree(msg->detached_data.pbData);
    ContextPropertyList_Free(msg->properties);
}