#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ strip; } ;
struct TYPE_14__ {int /*<<< orphan*/  maxstacksize; int /*<<< orphan*/  is_vararg; int /*<<< orphan*/  numparams; int /*<<< orphan*/  nups; int /*<<< orphan*/  lastlinedefined; int /*<<< orphan*/  linedefined; int /*<<< orphan*/  const* source; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ Proto ;
typedef  TYPE_2__ DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpChar (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  DumpCode (TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  DumpConstants (TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  DumpDebug (TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  DumpInt (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  DumpString (int /*<<< orphan*/  const*,TYPE_2__*) ; 

__attribute__((used)) static void DumpFunction(const Proto* f, const TString* p, DumpState* D)
{
 DumpString((f->source==p || D->strip) ? NULL : f->source,D);
 DumpInt(f->linedefined,D);
 DumpInt(f->lastlinedefined,D);
 DumpChar(f->nups,D);
 DumpChar(f->numparams,D);
 DumpChar(f->is_vararg,D);
 DumpChar(f->maxstacksize,D);
 DumpCode(f,D);
 DumpConstants(f,D);
 DumpDebug(f,D);
}