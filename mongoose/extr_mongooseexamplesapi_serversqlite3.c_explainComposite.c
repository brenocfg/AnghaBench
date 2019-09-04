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
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_3__ {int explain; int /*<<< orphan*/  iSelectId; int /*<<< orphan*/  db; int /*<<< orphan*/ * pVdbe; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Explain ; 
 int /*<<< orphan*/  P4_DYNAMIC ; 
 int TK_ALL ; 
 int TK_EXCEPT ; 
 int TK_INTERSECT ; 
 int TK_UNION ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  selectOpName (int) ; 
 char* sqlite3MPrintf (int /*<<< orphan*/ ,char*,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void explainComposite(
  Parse *pParse,                  /* Parse context */
  int op,                         /* One of TK_UNION, TK_EXCEPT etc. */
  int iSub1,                      /* Subquery id 1 */
  int iSub2,                      /* Subquery id 2 */
  int bUseTmp                     /* True if a temp table was used */
){
  assert( op==TK_UNION || op==TK_EXCEPT || op==TK_INTERSECT || op==TK_ALL );
  if( pParse->explain==2 ){
    Vdbe *v = pParse->pVdbe;
    char *zMsg = sqlite3MPrintf(
        pParse->db, "COMPOUND SUBQUERIES %d AND %d %s(%s)", iSub1, iSub2,
        bUseTmp?"USING TEMP B-TREE ":"", selectOpName(op)
    );
    sqlite3VdbeAddOp4(v, OP_Explain, pParse->iSelectId, 0, 0, zMsg, P4_DYNAMIC);
  }
}