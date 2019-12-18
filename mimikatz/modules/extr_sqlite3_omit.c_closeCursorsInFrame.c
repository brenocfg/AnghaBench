#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VdbeCursor ;
struct TYPE_4__ {int nCursor; int /*<<< orphan*/ ** apCsr; } ;
typedef  TYPE_1__ Vdbe ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3VdbeFreeCursor (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void closeCursorsInFrame(Vdbe *p){
  if( p->apCsr ){
    int i;
    for(i=0; i<p->nCursor; i++){
      VdbeCursor *pC = p->apCsr[i];
      if( pC ){
        sqlite3VdbeFreeCursor(p, pC);
        p->apCsr[i] = 0;
      }
    }
  }
}