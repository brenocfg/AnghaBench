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
typedef  int /*<<< orphan*/  vtbl_method_t ;
struct TYPE_3__ {int /*<<< orphan*/  Release; int /*<<< orphan*/  AddRef; int /*<<< orphan*/  QueryInterface; } ;
typedef  TYPE_1__ IUnknownVtbl ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int MAX_BLOCKS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * allocate_block (int) ; 
 int /*<<< orphan*/  delegating_AddRef ; 
 int /*<<< orphan*/  delegating_QueryInterface ; 
 int /*<<< orphan*/  delegating_Release ; 
 int /*<<< orphan*/ ** method_blocks ; 

__attribute__((used)) static BOOL fill_delegated_stub_table(IUnknownVtbl *vtbl, DWORD num)
{
    const void **entry = (const void **)(vtbl + 1);
    DWORD i, j;

    if (num - 3 > BLOCK_SIZE * MAX_BLOCKS)
    {
        FIXME( "%u methods not supported\n", num );
        return FALSE;
    }
    vtbl->QueryInterface = delegating_QueryInterface;
    vtbl->AddRef = delegating_AddRef;
    vtbl->Release = delegating_Release;
    for (i = 0; i < (num - 3 + BLOCK_SIZE - 1) / BLOCK_SIZE; i++)
    {
        const vtbl_method_t *block = method_blocks[i];
        if (!block && !(block = allocate_block( i ))) return FALSE;
        for (j = 0; j < BLOCK_SIZE && j < num - 3 - i * BLOCK_SIZE; j++) *entry++ = &block[j];
    }
    return TRUE;
}