#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int av_len; int /*<<< orphan*/  av_val; } ;
typedef  TYPE_1__ AVal ;

/* Variables and functions */
 char* AMF_EncodeInt16 (char*,char*,int) ; 
 char* AMF_EncodeString (char*,char*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

char *
AMF_EncodeNamedString(char *output, char *outend, const AVal *strName, const AVal *strValue)
{
    if (output+2+strName->av_len > outend)
        return NULL;
    output = AMF_EncodeInt16(output, outend, strName->av_len);

    memcpy(output, strName->av_val, strName->av_len);
    output += strName->av_len;

    return AMF_EncodeString(output, outend, strValue);
}