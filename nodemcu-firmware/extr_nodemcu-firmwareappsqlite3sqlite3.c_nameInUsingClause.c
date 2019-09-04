#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nId; TYPE_1__* a; } ;
struct TYPE_4__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_2__ IdList ;

/* Variables and functions */
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int nameInUsingClause(IdList *pUsing, const char *zCol){
  if( pUsing ){
    int k;
    for(k=0; k<pUsing->nId; k++){
      if( sqlite3StrICmp(pUsing->a[k].zName, zCol)==0 ) return 1;
    }
  }
  return 0;
}