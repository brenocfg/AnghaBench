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
struct TYPE_5__ {size_t major; int /*<<< orphan*/  minor; } ;
typedef  TYPE_1__ yyStackEntry ;
struct TYPE_6__ {size_t yyidx; TYPE_1__* yystack; } ;
typedef  TYPE_2__ yyParser ;
typedef  int YYCODETYPE ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*,char*) ; 
 char** yyTokenName ; 
 scalar_t__ yyTraceFILE ; 
 char* yyTracePrompt ; 
 int /*<<< orphan*/  yy_destructor (TYPE_2__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  /* There is no mechanism by which the parser stack can be popped below
  ** empty in SQLite.  */
  if( NEVER(pParser->yyidx<0) ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}