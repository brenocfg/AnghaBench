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
struct TYPE_3__ {int sizecode; int /*<<< orphan*/ * code; } ;
typedef  TYPE_1__ Proto ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  int /*<<< orphan*/  DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  Align4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpBlock (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpInt (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MaybeByteSwap (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void DumpCode(const Proto *f, DumpState* D)
{
 DumpInt(f->sizecode,D);
 char buf[10];
 int i;
 Align4(D);
 for (i=0; i<f->sizecode; i++)
 {
  memcpy(buf,&f->code[i],sizeof(Instruction));
  MaybeByteSwap(buf,sizeof(Instruction),D);
  DumpBlock(buf,sizeof(Instruction),D);
 }
}