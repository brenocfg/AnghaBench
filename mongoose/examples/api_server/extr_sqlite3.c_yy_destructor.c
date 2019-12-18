#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yyParser ;
struct TYPE_9__ {int /*<<< orphan*/  b; } ;
struct TYPE_8__ {int /*<<< orphan*/  pSelect; int /*<<< orphan*/  pList; } ;
struct TYPE_7__ {int /*<<< orphan*/  pExpr; } ;
struct TYPE_10__ {TYPE_3__ yy410; int /*<<< orphan*/  yy327; TYPE_2__ yy487; int /*<<< orphan*/  yy180; int /*<<< orphan*/  yy122; int /*<<< orphan*/  yy347; int /*<<< orphan*/  yy442; TYPE_1__ yy342; int /*<<< orphan*/  yy159; } ;
typedef  TYPE_4__ YYMINORTYPE ;
typedef  int YYCODETYPE ;
struct TYPE_11__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 TYPE_6__* pParse ; 
 int /*<<< orphan*/  sqlite3DeleteTriggerStep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3IdListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ParserARG_FETCH ; 
 int /*<<< orphan*/  sqlite3SelectDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  sqlite3ParserARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    case 160: /* select */
    case 194: /* oneselect */
{
sqlite3SelectDelete(pParse->db, (yypminor->yy159));
}
      break;
    case 173: /* term */
    case 174: /* expr */
{
sqlite3ExprDelete(pParse->db, (yypminor->yy342).pExpr);
}
      break;
    case 178: /* idxlist_opt */
    case 187: /* idxlist */
    case 197: /* selcollist */
    case 200: /* groupby_opt */
    case 202: /* orderby_opt */
    case 204: /* sclp */
    case 214: /* sortlist */
    case 215: /* nexprlist */
    case 216: /* setlist */
    case 220: /* exprlist */
    case 225: /* case_exprlist */
{
sqlite3ExprListDelete(pParse->db, (yypminor->yy442));
}
      break;
    case 193: /* fullname */
    case 198: /* from */
    case 206: /* seltablist */
    case 207: /* stl_prefix */
{
sqlite3SrcListDelete(pParse->db, (yypminor->yy347));
}
      break;
    case 199: /* where_opt */
    case 201: /* having_opt */
    case 210: /* on_opt */
    case 224: /* case_operand */
    case 226: /* case_else */
    case 236: /* when_clause */
    case 241: /* key_opt */
{
sqlite3ExprDelete(pParse->db, (yypminor->yy122));
}
      break;
    case 211: /* using_opt */
    case 213: /* inscollist */
    case 218: /* inscollist_opt */
{
sqlite3IdListDelete(pParse->db, (yypminor->yy180));
}
      break;
    case 219: /* valuelist */
{

  sqlite3ExprListDelete(pParse->db, (yypminor->yy487).pList);
  sqlite3SelectDelete(pParse->db, (yypminor->yy487).pSelect);

}
      break;
    case 232: /* trigger_cmd_list */
    case 237: /* trigger_cmd */
{
sqlite3DeleteTriggerStep(pParse->db, (yypminor->yy327));
}
      break;
    case 234: /* trigger_event */
{
sqlite3IdListDelete(pParse->db, (yypminor->yy410).b);
}
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}