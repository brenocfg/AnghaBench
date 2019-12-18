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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {scalar_t__ OutputBuffer; scalar_t__ dwOutputCount; scalar_t__ dwCPOutputCount; } ;
typedef  TYPE_1__ RTF_Info ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  RTFFlushCPOutputBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  RTFFlushUnicodeOutputBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int min (int,scalar_t__) ; 

__attribute__((used)) static void
RTFPutUnicodeString(RTF_Info *info, const WCHAR *string, int length)
{
        if (info->dwCPOutputCount)
                RTFFlushCPOutputBuffer(info);
        while (length)
        {
                int fit = min(length, ARRAY_SIZE(info->OutputBuffer) - info->dwOutputCount);

                memmove(info->OutputBuffer + info->dwOutputCount, string, fit * sizeof(WCHAR));
                info->dwOutputCount += fit;
                length -= fit;
                string += fit;
                if (ARRAY_SIZE(info->OutputBuffer) == info->dwOutputCount)
                        RTFFlushUnicodeOutputBuffer(info);
        }
}