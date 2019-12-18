#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int o_num; } ;
struct TYPE_11__ {int /*<<< orphan*/  av_val; scalar_t__ av_len; } ;
struct TYPE_9__ {char* av_len; int /*<<< orphan*/  av_val; } ;
struct TYPE_10__ {unsigned char p_number; TYPE_1__ p_aval; TYPE_5__ p_object; } ;
struct TYPE_12__ {int p_type; TYPE_3__ p_name; TYPE_2__ p_vu; } ;
typedef  TYPE_4__ AMFObjectProperty ;
typedef  TYPE_5__ AMFObject ;

/* Variables and functions */
#define  AMF_BOOLEAN 134 
#define  AMF_DATE 133 
#define  AMF_ECMA_ARRAY 132 
 TYPE_4__* AMF_GetProp (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
#define  AMF_NUMBER 131 
#define  AMF_OBJECT 130 
#define  AMF_STRICT_ARRAY 129 
#define  AMF_STRING 128 
 int FALSE ; 
 int /*<<< orphan*/  RTMP_LOGINFO ; 
 int /*<<< orphan*/  RTMP_Log (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int
DumpMetaData(AMFObject *obj)
{
    AMFObjectProperty *prop;
    int n, len;
    for (n = 0; n < obj->o_num; n++)
    {
        char str[256] = "";
        prop = AMF_GetProp(obj, NULL, n);
        switch (prop->p_type)
        {
        case AMF_OBJECT:
        case AMF_ECMA_ARRAY:
        case AMF_STRICT_ARRAY:
            if (prop->p_name.av_len)
                RTMP_Log(RTMP_LOGINFO, "%.*s:", prop->p_name.av_len, prop->p_name.av_val);
            DumpMetaData(&prop->p_vu.p_object);
            break;
        case AMF_NUMBER:
            snprintf(str, 255, "%.2f", prop->p_vu.p_number);
            break;
        case AMF_BOOLEAN:
            snprintf(str, 255, "%s",
                     prop->p_vu.p_number != 0. ? "TRUE" : "FALSE");
            break;
        case AMF_STRING:
            len = snprintf(str, 255, "%.*s", prop->p_vu.p_aval.av_len,
                           prop->p_vu.p_aval.av_val);
            if (len >= 1 && str[len-1] == '\n')
                str[len-1] = '\0';
            break;
        case AMF_DATE:
            snprintf(str, 255, "timestamp:%.2f", prop->p_vu.p_number);
            break;
        default:
            snprintf(str, 255, "INVALID TYPE 0x%02x",
                     (unsigned char)prop->p_type);
        }
        if (str[0] && prop->p_name.av_len)
        {
            RTMP_Log(RTMP_LOGINFO, "  %-22.*s%s", prop->p_name.av_len,
                     prop->p_name.av_val, str);
        }
    }
    return FALSE;
}