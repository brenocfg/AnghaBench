#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum cpu_addr { ____Placeholder_cpu_addr } cpu_addr ;
struct TYPE_6__ {int /*<<< orphan*/  Offset; int /*<<< orphan*/  Segment; int /*<<< orphan*/  Mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  Iar; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_1__ CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_2__ ADDRESS64 ;

/* Variables and functions */
 int /*<<< orphan*/  AddrModeFlat ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRUE ; 
#define  cpu_addr_frame 130 
#define  cpu_addr_pc 129 
#define  cpu_addr_stack 128 

__attribute__((used)) static BOOL ppc_get_addr(HANDLE hThread, const CONTEXT* ctx,
                         enum cpu_addr ca, ADDRESS64* addr)
{
   switch (ca)
    {
#if defined(__powerpc__)
    case cpu_addr_pc:
        addr->Mode    = AddrModeFlat;
        addr->Segment = 0; /* don't need segment */
        addr->Offset  = ctx->Iar;
        return TRUE;
#endif
    default:
    case cpu_addr_stack:
    case cpu_addr_frame:
        FIXME("not done\n");
    }
    return FALSE;
}