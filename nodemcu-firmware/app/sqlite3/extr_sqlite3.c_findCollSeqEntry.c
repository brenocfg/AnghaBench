#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  aCollSeq; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_14__ {char* zName; int /*<<< orphan*/  enc; } ;
typedef  TYPE_2__ CollSeq ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_UTF16BE ; 
 int /*<<< orphan*/  SQLITE_UTF16LE ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* sqlite3DbMallocZero (TYPE_1__*,int) ; 
 TYPE_2__* sqlite3HashFind (int /*<<< orphan*/ *,char const*) ; 
 TYPE_2__* sqlite3HashInsert (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3OomFault (TYPE_1__*) ; 
 int sqlite3Strlen30 (char const*) ; 

__attribute__((used)) static CollSeq *findCollSeqEntry(
  sqlite3 *db,          /* Database connection */
  const char *zName,    /* Name of the collating sequence */
  int create            /* Create a new entry if true */
){
  CollSeq *pColl;
  pColl = sqlite3HashFind(&db->aCollSeq, zName);

  if( 0==pColl && create ){
    int nName = sqlite3Strlen30(zName);
    pColl = sqlite3DbMallocZero(db, 3*sizeof(*pColl) + nName + 1);
    if( pColl ){
      CollSeq *pDel = 0;
      pColl[0].zName = (char*)&pColl[3];
      pColl[0].enc = SQLITE_UTF8;
      pColl[1].zName = (char*)&pColl[3];
      pColl[1].enc = SQLITE_UTF16LE;
      pColl[2].zName = (char*)&pColl[3];
      pColl[2].enc = SQLITE_UTF16BE;
      memcpy(pColl[0].zName, zName, nName);
      pColl[0].zName[nName] = 0;
      pDel = sqlite3HashInsert(&db->aCollSeq, pColl[0].zName, pColl);

      /* If a malloc() failure occurred in sqlite3HashInsert(), it will
      ** return the pColl pointer to be deleted (because it wasn't added
      ** to the hash table).
      */
      assert( pDel==0 || pDel==pColl );
      if( pDel!=0 ){
        sqlite3OomFault(db);
        sqlite3DbFree(db, pDel);
        pColl = 0;
      }
    }
  }
  return pColl;
}