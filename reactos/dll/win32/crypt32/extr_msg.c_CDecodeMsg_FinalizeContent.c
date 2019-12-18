#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; } ;
typedef  int /*<<< orphan*/  CRYPT_DER_BLOB ;
typedef  TYPE_1__ CDecodeMsg ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CDecodeMsg_FinalizeEnvelopedContent (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CDecodeMsg_FinalizeHashedContent (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CDecodeMsg_FinalizeSignedContent (TYPE_1__*,int /*<<< orphan*/ *) ; 
#define  CMSG_ENVELOPED 130 
#define  CMSG_HASHED 129 
#define  CMSG_SIGNED 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL CDecodeMsg_FinalizeContent(CDecodeMsg *msg, CRYPT_DER_BLOB *blob)
{
    BOOL ret = FALSE;

    switch (msg->type)
    {
    case CMSG_HASHED:
        ret = CDecodeMsg_FinalizeHashedContent(msg, blob);
        break;
    case CMSG_ENVELOPED:
        ret = CDecodeMsg_FinalizeEnvelopedContent(msg, blob);
        break;
    case CMSG_SIGNED:
        ret = CDecodeMsg_FinalizeSignedContent(msg, blob);
        break;
    default:
        ret = TRUE;
    }
    return ret;
}