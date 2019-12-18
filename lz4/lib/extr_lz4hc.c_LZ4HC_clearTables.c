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
struct TYPE_3__ {void* chainTable; scalar_t__ hashTable; } ;
typedef  TYPE_1__ LZ4HC_CCtx_internal ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_INIT (void*,int,int) ; 

__attribute__((used)) static void LZ4HC_clearTables (LZ4HC_CCtx_internal* hc4)
{
    MEM_INIT((void*)hc4->hashTable, 0, sizeof(hc4->hashTable));
    MEM_INIT(hc4->chainTable, 0xFF, sizeof(hc4->chainTable));
}