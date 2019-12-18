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
struct TYPE_3__ {int nColumn; char** azColl; } ;
typedef  TYPE_1__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3StrICmp (char const*,char const*) ; 

__attribute__((used)) static int collationMatch(const char *zColl, Index *pIndex){
  int i;
  assert( zColl!=0 );
  for(i=0; i<pIndex->nColumn; i++){
    const char *z = pIndex->azColl[i];
    assert( z!=0 );
    if( 0==sqlite3StrICmp(z, zColl) ){
      return 1;
    }
  }
  return 0;
}