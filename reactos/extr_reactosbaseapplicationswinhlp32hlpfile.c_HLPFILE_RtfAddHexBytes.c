#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct RtfData {scalar_t__ in_text; } ;
typedef  int BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HLPFILE_RtfAddRawString (struct RtfData*,char*,int) ; 
 scalar_t__ TRUE ; 
 unsigned int min (int,unsigned int) ; 

__attribute__((used)) static BOOL HLPFILE_RtfAddHexBytes(struct RtfData* rd, const void* _ptr, unsigned sz)
{
    char        tmp[512];
    unsigned    i, step;
    const BYTE* ptr = _ptr;
    static const char* _2hex = "0123456789abcdef";

    if (!rd->in_text)
    {
        if (!HLPFILE_RtfAddRawString(rd, " ", 1)) return FALSE;
        rd->in_text = TRUE;
    }
    for (; sz; sz -= step)
    {
        step = min(256, sz);
        for (i = 0; i < step; i++)
        {
            tmp[2 * i + 0] = _2hex[*ptr >> 4];
            tmp[2 * i + 1] = _2hex[*ptr++ & 0xF];
        }
        if (!HLPFILE_RtfAddRawString(rd, tmp, 2 * step)) return FALSE;
    }
    return TRUE;
}