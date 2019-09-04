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
struct TYPE_3__ {int yyerrcnt; scalar_t__ yytos; scalar_t__ yystack; } ;
typedef  TYPE_1__ yyParser ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  sqlite3ParserARG_FETCH ; 
 int /*<<< orphan*/  sqlite3ParserARG_STORE ; 
 scalar_t__ yyTraceFILE ; 
 char* yyTracePrompt ; 

__attribute__((used)) static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  sqlite3ParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
/*********** End %parse_accept code *******************************************/
  sqlite3ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}