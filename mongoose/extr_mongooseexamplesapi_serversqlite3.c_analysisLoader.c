#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int tRowcnt ;
struct TYPE_6__ {int /*<<< orphan*/  zDatabase; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ analysisInfo ;
struct TYPE_7__ {int nRowEst; } ;
typedef  TYPE_2__ Table ;
struct TYPE_8__ {int nColumn; int* aiRowEst; int bUnordered; } ;
typedef  TYPE_3__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER2 (char**,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__* sqlite3FindIndex (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* sqlite3FindTable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int analysisLoader(void *pData, int argc, char **argv, char **NotUsed){
  analysisInfo *pInfo = (analysisInfo*)pData;
  Index *pIndex;
  Table *pTable;
  int i, c, n;
  tRowcnt v;
  const char *z;

  assert( argc==3 );
  UNUSED_PARAMETER2(NotUsed, argc);

  if( argv==0 || argv[0]==0 || argv[2]==0 ){
    return 0;
  }
  pTable = sqlite3FindTable(pInfo->db, argv[0], pInfo->zDatabase);
  if( pTable==0 ){
    return 0;
  }
  if( argv[1] ){
    pIndex = sqlite3FindIndex(pInfo->db, argv[1], pInfo->zDatabase);
  }else{
    pIndex = 0;
  }
  n = pIndex ? pIndex->nColumn : 0;
  z = argv[2];
  for(i=0; *z && i<=n; i++){
    v = 0;
    while( (c=z[0])>='0' && c<='9' ){
      v = v*10 + c - '0';
      z++;
    }
    if( i==0 ) pTable->nRowEst = v;
    if( pIndex==0 ) break;
    pIndex->aiRowEst[i] = v;
    if( *z==' ' ) z++;
    if( strcmp(z, "unordered")==0 ){
      pIndex->bUnordered = 1;
      break;
    }
  }
  return 0;
}