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
struct TYPE_3__ {scalar_t__ nArg; scalar_t__ nUsed; int /*<<< orphan*/ * apArg; } ;
typedef  TYPE_1__ PrintfArguments ;

/* Variables and functions */
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *getTextArg(PrintfArguments *p){
  if( p->nArg<=p->nUsed ) return 0;
  return (char*)sqlite3_value_text(p->apArg[p->nUsed++]);
}