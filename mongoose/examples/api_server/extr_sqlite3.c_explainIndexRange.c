#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_14__ {TYPE_6__* pIdx; } ;
struct TYPE_15__ {int nEq; int wsFlags; TYPE_1__ u; } ;
typedef  TYPE_2__ WherePlan ;
struct TYPE_16__ {TYPE_2__ plan; } ;
typedef  TYPE_3__ WhereLevel ;
struct TYPE_17__ {TYPE_7__* aCol; } ;
typedef  TYPE_4__ Table ;
struct TYPE_20__ {char* zName; } ;
struct TYPE_19__ {int* aiColumn; int nColumn; } ;
struct TYPE_18__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_5__ StrAccum ;
typedef  TYPE_6__ Index ;
typedef  TYPE_7__ Column ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_MAX_LENGTH ; 
 int WHERE_BTM_LIMIT ; 
 int WHERE_TOP_LIMIT ; 
 int /*<<< orphan*/  explainAppendTerm (TYPE_5__*,int,char*,char*) ; 
 int /*<<< orphan*/  sqlite3StrAccumAppend (TYPE_5__*,char*,int) ; 
 char* sqlite3StrAccumFinish (TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3StrAccumInit (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *explainIndexRange(sqlite3 *db, WhereLevel *pLevel, Table *pTab){
  WherePlan *pPlan = &pLevel->plan;
  Index *pIndex = pPlan->u.pIdx;
  int nEq = pPlan->nEq;
  int i, j;
  Column *aCol = pTab->aCol;
  int *aiColumn = pIndex->aiColumn;
  StrAccum txt;

  if( nEq==0 && (pPlan->wsFlags & (WHERE_BTM_LIMIT|WHERE_TOP_LIMIT))==0 ){
    return 0;
  }
  sqlite3StrAccumInit(&txt, 0, 0, SQLITE_MAX_LENGTH);
  txt.db = db;
  sqlite3StrAccumAppend(&txt, " (", 2);
  for(i=0; i<nEq; i++){
    explainAppendTerm(&txt, i, aCol[aiColumn[i]].zName, "=");
  }

  j = i;
  if( pPlan->wsFlags&WHERE_BTM_LIMIT ){
    char *z = (j==pIndex->nColumn ) ? "rowid" : aCol[aiColumn[j]].zName;
    explainAppendTerm(&txt, i++, z, ">");
  }
  if( pPlan->wsFlags&WHERE_TOP_LIMIT ){
    char *z = (j==pIndex->nColumn ) ? "rowid" : aCol[aiColumn[j]].zName;
    explainAppendTerm(&txt, i, z, "<");
  }
  sqlite3StrAccumAppend(&txt, ")", 1);
  return sqlite3StrAccumFinish(&txt);
}