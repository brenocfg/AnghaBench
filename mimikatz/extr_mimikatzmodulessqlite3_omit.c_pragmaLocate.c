#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_1__ PragmaName ;

/* Variables and functions */
 int ArraySize (TYPE_1__ const*) ; 
 TYPE_1__ const* aPragmaName ; 
 int sqlite3_stricmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const PragmaName *pragmaLocate(const char *zName){
  int upr, lwr, mid = 0, rc;
  lwr = 0;
  upr = ArraySize(aPragmaName)-1;
  while( lwr<=upr ){
    mid = (lwr+upr)/2;
    rc = sqlite3_stricmp(zName, aPragmaName[mid].zName);
    if( rc==0 ) break;
    if( rc<0 ){
      upr = mid - 1;
    }else{
      lwr = mid + 1;
    }
  }
  return lwr>upr ? 0 : &aPragmaName[mid];
}