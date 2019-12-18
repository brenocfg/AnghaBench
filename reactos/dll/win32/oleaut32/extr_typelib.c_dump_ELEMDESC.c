#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
struct TYPE_9__ {int /*<<< orphan*/  vt; } ;
struct TYPE_6__ {int wParamFlags; int /*<<< orphan*/  pparamdescex; } ;
struct TYPE_7__ {TYPE_1__ paramdesc; } ;
struct TYPE_8__ {TYPE_2__ u; TYPE_4__ tdesc; } ;
typedef  TYPE_3__ ELEMDESC ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE (char*,...) ; 
 int PARAMFLAG_FHASCUSTDATA ; 
 int PARAMFLAG_FHASDEFAULT ; 
 int PARAMFLAG_FIN ; 
 int PARAMFLAG_FLCID ; 
 int PARAMFLAG_FOPT ; 
 int PARAMFLAG_FOUT ; 
 int PARAMFLAG_FRETVAL ; 
 int /*<<< orphan*/  dump_TypeDesc (TYPE_4__*,char*) ; 

__attribute__((used)) static void dump_ELEMDESC(const ELEMDESC *edesc) {
  char buf[200];
  USHORT flags = edesc->u.paramdesc.wParamFlags;
  dump_TypeDesc(&edesc->tdesc,buf);
  MESSAGE("\t\ttdesc.vartype %d (%s)\n",edesc->tdesc.vt,buf);
  MESSAGE("\t\tu.paramdesc.wParamFlags");
  if (!flags) MESSAGE(" PARAMFLAGS_NONE");
  if (flags & PARAMFLAG_FIN) MESSAGE(" PARAMFLAG_FIN");
  if (flags & PARAMFLAG_FOUT) MESSAGE(" PARAMFLAG_FOUT");
  if (flags & PARAMFLAG_FLCID) MESSAGE(" PARAMFLAG_FLCID");
  if (flags & PARAMFLAG_FRETVAL) MESSAGE(" PARAMFLAG_FRETVAL");
  if (flags & PARAMFLAG_FOPT) MESSAGE(" PARAMFLAG_FOPT");
  if (flags & PARAMFLAG_FHASDEFAULT) MESSAGE(" PARAMFLAG_FHASDEFAULT");
  if (flags & PARAMFLAG_FHASCUSTDATA) MESSAGE(" PARAMFLAG_FHASCUSTDATA");
  MESSAGE("\n\t\tu.paramdesc.lpex %p\n",edesc->u.paramdesc.pparamdescex);
}