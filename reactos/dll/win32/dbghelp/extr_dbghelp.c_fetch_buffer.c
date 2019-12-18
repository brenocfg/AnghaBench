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
struct process {unsigned int buffer_size; void* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 void* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int) ; 

void* fetch_buffer(struct process* pcs, unsigned size)
{
    if (size > pcs->buffer_size)
    {
        if (pcs->buffer)
            pcs->buffer = HeapReAlloc(GetProcessHeap(), 0, pcs->buffer, size);
        else
            pcs->buffer = HeapAlloc(GetProcessHeap(), 0, size);
        pcs->buffer_size = (pcs->buffer) ? size : 0;
    }
    return pcs->buffer;
}