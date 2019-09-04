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
typedef  int /*<<< orphan*/  voidpf ;
typedef  int uInt ;

/* Variables and functions */
 int /*<<< orphan*/  ProcessHeap ; 
 int /*<<< orphan*/  RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

voidpf
MSZipAlloc(voidpf opaque, uInt items, uInt size)
{
    return (voidpf)RtlAllocateHeap(ProcessHeap, 0, items * size);
}