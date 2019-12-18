#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum cpu_addr { ____Placeholder_cpu_addr } cpu_addr ;
struct TYPE_10__ {int Mode; int /*<<< orphan*/  Offset; scalar_t__ Segment; } ;
struct TYPE_7__ {int /*<<< orphan*/  Fp; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct TYPE_9__ {TYPE_2__ u; int /*<<< orphan*/  Sp; int /*<<< orphan*/  Pc; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_3__ CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_4__ ADDRESS64 ;

/* Variables and functions */
 int AddrModeFlat ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  cpu_addr_frame 130 
#define  cpu_addr_pc 129 
#define  cpu_addr_stack 128 

__attribute__((used)) static BOOL arm64_get_addr(HANDLE hThread, const CONTEXT* ctx,
                           enum cpu_addr ca, ADDRESS64* addr)
{
    addr->Mode    = AddrModeFlat;
    addr->Segment = 0; /* don't need segment */
    switch (ca)
    {
#ifdef __aarch64__
    case cpu_addr_pc:    addr->Offset = ctx->Pc;  return TRUE;
    case cpu_addr_stack: addr->Offset = ctx->Sp;  return TRUE;
    case cpu_addr_frame: addr->Offset = ctx->u.s.Fp; return TRUE;
#endif
    default: addr->Mode = -1;
        return FALSE;
    }
}