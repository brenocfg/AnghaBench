#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * o_props; scalar_t__ o_num; } ;
typedef  int /*<<< orphan*/  AMFObjectProperty ;
typedef  TYPE_1__ AMFObject ;

/* Variables and functions */
 int AMFProp_Decode (int /*<<< orphan*/ *,char const*,int,int) ; 
 int /*<<< orphan*/  AMF_AddProp (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int TRUE ; 

int
AMF_DecodeArray(AMFObject *obj, const char *pBuffer, int nSize,
                int nArrayLen, int bDecodeName)
{
    int nOriginalSize = nSize;
    int bError = FALSE;

    obj->o_num = 0;
    obj->o_props = NULL;
    while (nArrayLen > 0)
    {
        AMFObjectProperty prop;
        int nRes;
        nArrayLen--;

        if (nSize <= 0)
        {
            bError = TRUE;
            break;
        }

        nRes = AMFProp_Decode(&prop, pBuffer, nSize, bDecodeName);
        if (nRes == -1)
        {
            bError = TRUE;
            break;
        }
        else
        {
            nSize -= nRes;
            pBuffer += nRes;
            AMF_AddProp(obj, &prop);
        }
    }
    if (bError)
        return -1;

    return nOriginalSize - nSize;
}