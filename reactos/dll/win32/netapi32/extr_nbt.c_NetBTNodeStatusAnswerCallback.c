#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int UCHAR ;
struct TYPE_6__ {int* astatLen; TYPE_1__* astat; scalar_t__ gotResponse; } ;
struct TYPE_5__ {int /*<<< orphan*/  name_flags; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int name_count; int adapter_type; int /*<<< orphan*/  adapter_address; } ;
typedef  int* PUCHAR ;
typedef  TYPE_2__* PNAME_BUFFER ;
typedef  TYPE_3__ NetBTNodeQueryData ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ADAPTER_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DEREGISTERED ; 
 int /*<<< orphan*/  DUPLICATE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GROUP_NAME ; 
 int NCBNAMSZ ; 
 int /*<<< orphan*/  REGISTERED ; 
 int /*<<< orphan*/  REGISTERING ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int min (int,int) ; 

__attribute__((used)) static BOOL NetBTNodeStatusAnswerCallback(void *pVoid, WORD answerCount,
 WORD answerIndex, PUCHAR rData, WORD rLen)
{
    NetBTNodeQueryData *data = pVoid;

    if (data && !data->gotResponse && rData && rLen >= 1)
    {
        /* num names is first byte; each name is NCBNAMSZ + 2 bytes */
        if (rLen >= rData[0] * (NCBNAMSZ + 2))
        {
            WORD i;
            PUCHAR src;
            PNAME_BUFFER dst;

            data->gotResponse = TRUE;
            data->astat->name_count = rData[0];
            for (i = 0, src = rData + 1,
             dst = (PNAME_BUFFER)((PUCHAR)data->astat +
              sizeof(ADAPTER_STATUS));
             i < data->astat->name_count && src - rData < rLen &&
             (PUCHAR)dst - (PUCHAR)data->astat < data->astatLen;
             i++, dst++, src += NCBNAMSZ + 2)
            {
                UCHAR flags = *(src + NCBNAMSZ);

                memcpy(dst->name, src, NCBNAMSZ);
                /* we won't actually see a registering name in the returned
                 * response.  It's useful to see if no other flags are set; if
                 * none are, then the name is registered. */
                dst->name_flags = REGISTERING;
                if (flags & 0x80)
                    dst->name_flags |= GROUP_NAME;
                if (flags & 0x10)
                    dst->name_flags |= DEREGISTERED;
                if (flags & 0x08)
                    dst->name_flags |= DUPLICATE;
                if (dst->name_flags == REGISTERING)
                    dst->name_flags = REGISTERED;
            }
            /* arbitrarily set HW type to Ethernet */
            data->astat->adapter_type = 0xfe;
            if (src - rData < rLen)
                memcpy(data->astat->adapter_address, src,
                 min(rLen - (src - rData), 6));
        }
    }
    return FALSE;
}