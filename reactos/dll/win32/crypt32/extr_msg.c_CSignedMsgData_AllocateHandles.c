#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cSignerHandle; int /*<<< orphan*/ * signerHandles; TYPE_1__* info; } ;
struct TYPE_4__ {int cSignerInfo; } ;
typedef  int /*<<< orphan*/  CSignerHandles ;
typedef  TYPE_2__ CSignedMsgData ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CryptMemAlloc (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL CSignedMsgData_AllocateHandles(CSignedMsgData *msg_data)
{
    BOOL ret = TRUE;

    if (msg_data->info->cSignerInfo)
    {
        msg_data->signerHandles =
         CryptMemAlloc(msg_data->info->cSignerInfo * sizeof(CSignerHandles));
        if (msg_data->signerHandles)
        {
            msg_data->cSignerHandle = msg_data->info->cSignerInfo;
            memset(msg_data->signerHandles, 0,
             msg_data->info->cSignerInfo * sizeof(CSignerHandles));
        }
        else
        {
            msg_data->cSignerHandle = 0;
            ret = FALSE;
        }
    }
    else
    {
        msg_data->cSignerHandle = 0;
        msg_data->signerHandles = NULL;
    }
    return ret;
}