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
struct proto {int val; int code; } ;
struct TYPE_3__ {int State; int Width; int Param; } ;
typedef  TYPE_1__ TIFFFaxTabEnt ;

/* Variables and functions */

__attribute__((used)) static void
FillTable(TIFFFaxTabEnt *T, int Size, struct proto *P, int State)
{
    int limit = 1 << Size;

    while (P->val) {
	int width = P->val & 15;
	int param = P->val >> 4;
	int incr = 1 << width;
	int code;
	for (code = P->code; code < limit; code += incr) {
	    TIFFFaxTabEnt *E = T+code;
	    E->State = State;
	    E->Width = width;
	    E->Param = param;
	}
	P++;
    }
}