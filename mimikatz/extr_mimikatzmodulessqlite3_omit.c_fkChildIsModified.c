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
struct TYPE_7__ {int iPKey; } ;
typedef  TYPE_2__ Table ;
struct TYPE_8__ {int nCol; TYPE_1__* aCol; } ;
struct TYPE_6__ {int iFrom; } ;
typedef  TYPE_3__ FKey ;

/* Variables and functions */

__attribute__((used)) static int fkChildIsModified(
  Table *pTab,                    /* Table being updated */
  FKey *p,                        /* Foreign key for which pTab is the child */
  int *aChange,                   /* Array indicating modified columns */
  int bChngRowid                  /* True if rowid is modified by this update */
){
  int i;
  for(i=0; i<p->nCol; i++){
    int iChildKey = p->aCol[i].iFrom;
    if( aChange[iChildKey]>=0 ) return 1;
    if( iChildKey==pTab->iPKey && bChngRowid ) return 1;
  }
  return 0;
}