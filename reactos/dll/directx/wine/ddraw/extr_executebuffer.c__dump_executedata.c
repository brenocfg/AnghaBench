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
struct TYPE_3__ {int /*<<< orphan*/  dwHVertexOffset; int /*<<< orphan*/  dwInstructionLength; int /*<<< orphan*/  dwInstructionOffset; int /*<<< orphan*/  dwVertexCount; int /*<<< orphan*/  dwVertexOffset; int /*<<< orphan*/  dwSize; } ;
typedef  TYPE_1__ D3DEXECUTEDATA ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void _dump_executedata(const D3DEXECUTEDATA *lpData) {
    TRACE("dwSize : %d\n", lpData->dwSize);
    TRACE("Vertex      Offset : %d  Count  : %d\n", lpData->dwVertexOffset, lpData->dwVertexCount);
    TRACE("Instruction Offset : %d  Length : %d\n", lpData->dwInstructionOffset, lpData->dwInstructionLength);
    TRACE("HVertex     Offset : %d\n", lpData->dwHVertexOffset);
}