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
struct TYPE_3__ {int eDest; } ;
typedef  TYPE_1__ SelectDest ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int SRT_Mem ; 
 int SRT_Set ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int checkForMultiColumnSelectError(
  Parse *pParse,       /* Parse context. */
  SelectDest *pDest,   /* Destination of SELECT results */
  int nExpr            /* Number of result columns returned by SELECT */
){
  int eDest = pDest->eDest;
  if( nExpr>1 && (eDest==SRT_Mem || eDest==SRT_Set) ){
    sqlite3ErrorMsg(pParse, "only a single result allowed for "
       "a SELECT that is part of an expression");
    return 1;
  }else{
    return 0;
  }
}