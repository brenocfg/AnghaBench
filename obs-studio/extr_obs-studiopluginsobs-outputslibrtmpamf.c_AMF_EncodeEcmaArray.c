#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int o_num; int /*<<< orphan*/ * o_props; } ;
typedef  TYPE_1__ AMFObject ;

/* Variables and functions */
 char* AMFProp_Encode (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  AMF_ECMA_ARRAY ; 
 char* AMF_EncodeInt24 (char*,char*,int /*<<< orphan*/ ) ; 
 char* AMF_EncodeInt32 (char*,char*,int) ; 
 int /*<<< orphan*/  AMF_OBJECT_END ; 
 int /*<<< orphan*/  RTMP_LOGERROR ; 
 int /*<<< orphan*/  RTMP_Log (int /*<<< orphan*/ ,char*,int) ; 

char *
AMF_EncodeEcmaArray(AMFObject *obj, char *pBuffer, char *pBufEnd)
{
    int i;

    if (pBuffer+4 >= pBufEnd)
        return NULL;

    *pBuffer++ = AMF_ECMA_ARRAY;

    pBuffer = AMF_EncodeInt32(pBuffer, pBufEnd, obj->o_num);

    for (i = 0; i < obj->o_num; i++)
    {
        char *res = AMFProp_Encode(&obj->o_props[i], pBuffer, pBufEnd);
        if (res == NULL)
        {
            RTMP_Log(RTMP_LOGERROR, "AMF_Encode - failed to encode property in index %d",
                     i);
            break;
        }
        else
        {
            pBuffer = res;
        }
    }

    if (pBuffer + 3 >= pBufEnd)
        return NULL;			/* no room for the end marker */

    pBuffer = AMF_EncodeInt24(pBuffer, pBufEnd, AMF_OBJECT_END);

    return pBuffer;
}