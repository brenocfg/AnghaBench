#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int tabFlags; } ;
typedef  TYPE_1__ Table ;
struct TYPE_13__ {int flags; } ;
struct TYPE_12__ {int iDb; int regCtr; TYPE_1__* pTab; struct TYPE_12__* pNext; } ;
struct TYPE_11__ {int nMem; TYPE_3__* pAinc; TYPE_7__* db; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ AutoincInfo ;

/* Variables and functions */
 int SQLITE_Vacuum ; 
 int TF_Autoincrement ; 
 TYPE_3__* sqlite3DbMallocRawNN (TYPE_7__*,int) ; 
 TYPE_2__* sqlite3ParseToplevel (TYPE_2__*) ; 

__attribute__((used)) static int autoIncBegin(
  Parse *pParse,      /* Parsing context */
  int iDb,            /* Index of the database holding pTab */
  Table *pTab         /* The table we are writing to */
){
  int memId = 0;      /* Register holding maximum rowid */
  if( (pTab->tabFlags & TF_Autoincrement)!=0
   && (pParse->db->flags & SQLITE_Vacuum)==0
  ){
    Parse *pToplevel = sqlite3ParseToplevel(pParse);
    AutoincInfo *pInfo;

    pInfo = pToplevel->pAinc;
    while( pInfo && pInfo->pTab!=pTab ){ pInfo = pInfo->pNext; }
    if( pInfo==0 ){
      pInfo = sqlite3DbMallocRawNN(pParse->db, sizeof(*pInfo));
      if( pInfo==0 ) return 0;
      pInfo->pNext = pToplevel->pAinc;
      pToplevel->pAinc = pInfo;
      pInfo->pTab = pTab;
      pInfo->iDb = iDb;
      pToplevel->nMem++;                  /* Register to hold name of table */
      pInfo->regCtr = ++pToplevel->nMem;  /* Max rowid register */
      pToplevel->nMem++;                  /* Rowid in sqlite_sequence */
    }
    memId = pInfo->regCtr;
  }
  return memId;
}