#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yyParser ;
struct TYPE_5__ {int /*<<< orphan*/  pExpr; } ;
struct TYPE_6__ {int /*<<< orphan*/  yy432; int /*<<< orphan*/  yy362; int /*<<< orphan*/  yy163; int /*<<< orphan*/  yy259; int /*<<< orphan*/  yy250; TYPE_1__ yy382; int /*<<< orphan*/  yy219; } ;
typedef  TYPE_2__ YYMINORTYPE ;
typedef  int YYCODETYPE ;
struct TYPE_7__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 TYPE_4__* pParse ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3IdListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ParserARG_FETCH ; 
 int /*<<< orphan*/  sqlite3SelectDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SrcListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3WithDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

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
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
    case 161: /* select */
    case 192: /* selectnowith */
    case 193: /* oneselect */
    case 203: /* values */
{
sqlite3SelectDelete(pParse->db, (yypminor->yy219));
}
      break;
    case 170: /* term */
    case 171: /* expr */
{
sqlite3ExprDelete(pParse->db, (yypminor->yy382).pExpr);
}
      break;
    case 175: /* eidlist_opt */
    case 184: /* sortlist */
    case 185: /* eidlist */
    case 196: /* selcollist */
    case 199: /* groupby_opt */
    case 201: /* orderby_opt */
    case 204: /* nexprlist */
    case 205: /* exprlist */
    case 206: /* sclp */
    case 215: /* setlist */
    case 221: /* paren_exprlist */
    case 223: /* case_exprlist */
{
sqlite3ExprListDelete(pParse->db, (yypminor->yy250));
}
      break;
    case 191: /* fullname */
    case 197: /* from */
    case 208: /* seltablist */
    case 209: /* stl_prefix */
{
sqlite3SrcListDelete(pParse->db, (yypminor->yy259));
}
      break;
    case 194: /* with */
    case 227: /* wqlist */
{
sqlite3WithDelete(pParse->db, (yypminor->yy163));
}
      break;
    case 198: /* where_opt */
    case 200: /* having_opt */
    case 212: /* on_opt */
    case 222: /* case_operand */
    case 224: /* case_else */
{
sqlite3ExprDelete(pParse->db, (yypminor->yy362));
}
      break;
    case 213: /* using_opt */
    case 214: /* idlist */
    case 217: /* idlist_opt */
{
sqlite3IdListDelete(pParse->db, (yypminor->yy432));
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}