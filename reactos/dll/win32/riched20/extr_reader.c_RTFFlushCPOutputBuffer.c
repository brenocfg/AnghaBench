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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int dwCPOutputCount; int /*<<< orphan*/  cpOutputBuffer; int /*<<< orphan*/  codePage; } ;
typedef  TYPE_1__ RTF_Info ;

/* Variables and functions */
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RTFPutUnicodeString (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
RTFFlushCPOutputBuffer(RTF_Info *info)
{
        int bufferMax = info->dwCPOutputCount * 2 * sizeof(WCHAR);
        WCHAR *buffer = heap_alloc(bufferMax);
        int length;

        length = MultiByteToWideChar(info->codePage, 0, info->cpOutputBuffer,
                                     info->dwCPOutputCount, buffer, bufferMax/sizeof(WCHAR));
        info->dwCPOutputCount = 0;

        RTFPutUnicodeString(info, buffer, length);
        heap_free(buffer);
}