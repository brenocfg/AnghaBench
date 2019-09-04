#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  int ULONG ;
typedef  size_t UCHAR ;
struct TYPE_2__ {int Offset; int ExtendedOffset; int /*<<< orphan*/  Access; int /*<<< orphan*/  Selector; } ;
typedef  scalar_t__ PVOID ;

/* Variables and functions */
 int /*<<< orphan*/  PMODE_CS ; 
 TYPE_1__* i386Idt ; 

__attribute__((used)) static
void
InitIdtVector(
    UCHAR Vector,
    PVOID ServiceHandler,
    USHORT Access)
{
    i386Idt[Vector].Offset = (ULONG)ServiceHandler & 0xffff;
    i386Idt[Vector].ExtendedOffset = (ULONG)ServiceHandler >> 16;
    i386Idt[Vector].Selector = PMODE_CS;
    i386Idt[Vector].Access = Access;
}