#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_11__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_10__ {scalar_t__ pNext; TYPE_2__* pParse; int /*<<< orphan*/ * pSrcList; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pExpr; } ;
typedef  int /*<<< orphan*/  SrcList ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ NameContext ;
typedef  TYPE_4__ ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  COLNAME_COLUMN ; 
 int /*<<< orphan*/  COLNAME_DATABASE ; 
 int /*<<< orphan*/  COLNAME_DECLTYPE ; 
 int /*<<< orphan*/  COLNAME_TABLE ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 char* columnType (TYPE_3__*,int /*<<< orphan*/ *,char const**,char const**,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeSetColName (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generateColumnTypes(
  Parse *pParse,      /* Parser context */
  SrcList *pTabList,  /* List of tables */
  ExprList *pEList    /* Expressions defining the result set */
){
#ifndef SQLITE_OMIT_DECLTYPE
  Vdbe *v = pParse->pVdbe;
  int i;
  NameContext sNC;
  sNC.pSrcList = pTabList;
  sNC.pParse = pParse;
  sNC.pNext = 0;
  for(i=0; i<pEList->nExpr; i++){
    Expr *p = pEList->a[i].pExpr;
    const char *zType;
#ifdef SQLITE_ENABLE_COLUMN_METADATA
    const char *zOrigDb = 0;
    const char *zOrigTab = 0;
    const char *zOrigCol = 0;
    zType = columnType(&sNC, p, &zOrigDb, &zOrigTab, &zOrigCol, 0);

    /* The vdbe must make its own copy of the column-type and other
    ** column specific strings, in case the schema is reset before this
    ** virtual machine is deleted.
    */
    sqlite3VdbeSetColName(v, i, COLNAME_DATABASE, zOrigDb, SQLITE_TRANSIENT);
    sqlite3VdbeSetColName(v, i, COLNAME_TABLE, zOrigTab, SQLITE_TRANSIENT);
    sqlite3VdbeSetColName(v, i, COLNAME_COLUMN, zOrigCol, SQLITE_TRANSIENT);
#else
    zType = columnType(&sNC, p, 0, 0, 0, 0);
#endif
    sqlite3VdbeSetColName(v, i, COLNAME_DECLTYPE, zType, SQLITE_TRANSIENT);
  }
#endif /* !defined(SQLITE_OMIT_DECLTYPE) */
}