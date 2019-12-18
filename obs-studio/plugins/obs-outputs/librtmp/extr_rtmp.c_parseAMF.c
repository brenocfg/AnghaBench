#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int o_num; TYPE_6__* o_props; } ;
struct TYPE_16__ {char* av_val; int /*<<< orphan*/  av_len; } ;
struct TYPE_17__ {void* p_number; TYPE_3__ p_aval; } ;
struct TYPE_15__ {char* av_val; int av_len; } ;
struct TYPE_14__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_21__ {scalar_t__ p_type; TYPE_4__ p_vu; TYPE_2__ p_name; TYPE_1__ member_0; } ;
struct TYPE_20__ {char* av_val; int /*<<< orphan*/  av_len; } ;
struct TYPE_18__ {TYPE_9__ p_object; } ;
struct TYPE_19__ {TYPE_5__ p_vu; } ;
typedef  TYPE_7__ AVal ;
typedef  TYPE_8__ AMFObjectProperty ;
typedef  TYPE_9__ AMFObject ;

/* Variables and functions */
 int /*<<< orphan*/  AMF_AddProp (TYPE_9__*,TYPE_8__*) ; 
 void* AMF_BOOLEAN ; 
 scalar_t__ AMF_NULL ; 
 void* AMF_NUMBER ; 
 scalar_t__ AMF_OBJECT ; 
 void* AMF_STRING ; 
 void* atoi (char*) ; 
 char* strchr (char*,char) ; 
 void* strtod (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
parseAMF(AMFObject *obj, AVal *av, int *depth)
{
    AMFObjectProperty prop = {{0,0}};
    int i;
    char *p, *arg = av->av_val;

    if (arg[1] == ':')
    {
        p = (char *)arg+2;
        switch(arg[0])
        {
        case 'B':
            prop.p_type = AMF_BOOLEAN;
            prop.p_vu.p_number = atoi(p);
            break;
        case 'S':
            prop.p_type = AMF_STRING;
            prop.p_vu.p_aval.av_val = p;
            prop.p_vu.p_aval.av_len = av->av_len - (p-arg);
            break;
        case 'N':
            prop.p_type = AMF_NUMBER;
            prop.p_vu.p_number = strtod(p, NULL);
            break;
        case 'Z':
            prop.p_type = AMF_NULL;
            break;
        case 'O':
            i = atoi(p);
            if (i)
            {
                prop.p_type = AMF_OBJECT;
            }
            else
            {
                (*depth)--;
                return 0;
            }
            break;
        default:
            return -1;
        }
    }
    else if (arg[2] == ':' && arg[0] == 'N')
    {
        p = strchr(arg+3, ':');
        if (!p || !*depth)
            return -1;
        prop.p_name.av_val = (char *)arg+3;
        prop.p_name.av_len = p - (arg+3);

        p++;
        switch(arg[1])
        {
        case 'B':
            prop.p_type = AMF_BOOLEAN;
            prop.p_vu.p_number = atoi(p);
            break;
        case 'S':
            prop.p_type = AMF_STRING;
            prop.p_vu.p_aval.av_val = p;
            prop.p_vu.p_aval.av_len = av->av_len - (p-arg);
            break;
        case 'N':
            prop.p_type = AMF_NUMBER;
            prop.p_vu.p_number = strtod(p, NULL);
            break;
        case 'O':
            prop.p_type = AMF_OBJECT;
            break;
        default:
            return -1;
        }
    }
    else
        return -1;

    if (*depth)
    {
        AMFObject *o2;
        for (i=0; i<*depth; i++)
        {
            o2 = &obj->o_props[obj->o_num-1].p_vu.p_object;
            obj = o2;
        }
    }
    AMF_AddProp(obj, &prop);
    if (prop.p_type == AMF_OBJECT)
        (*depth)++;
    return 0;
}