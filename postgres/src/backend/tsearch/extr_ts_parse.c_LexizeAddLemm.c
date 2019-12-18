#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tail; } ;
struct TYPE_7__ {TYPE_4__ towork; int /*<<< orphan*/  curSub; } ;
struct TYPE_6__ {int type; char* lemm; int lenlemm; } ;
typedef  TYPE_1__ ParsedLex ;
typedef  TYPE_2__ LexizeData ;

/* Variables and functions */
 int /*<<< orphan*/  LPLAddTail (TYPE_4__*,TYPE_1__*) ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static void
LexizeAddLemm(LexizeData *ld, int type, char *lemm, int lenlemm)
{
	ParsedLex  *newpl = (ParsedLex *) palloc(sizeof(ParsedLex));

	newpl->type = type;
	newpl->lemm = lemm;
	newpl->lenlemm = lenlemm;
	LPLAddTail(&ld->towork, newpl);
	ld->curSub = ld->towork.tail;
}