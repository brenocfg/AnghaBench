#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* aiColumn; TYPE_2__* pTable; } ;
struct TYPE_6__ {TYPE_1__* aCol; } ;
struct TYPE_5__ {char const* zName; } ;
typedef  TYPE_3__ Index ;

/* Variables and functions */
 int XN_EXPR ; 
 int XN_ROWID ; 

__attribute__((used)) static const char *explainIndexColumnName(Index *pIdx, int i){
  i = pIdx->aiColumn[i];
  if( i==XN_EXPR ) return "<expr>";
  if( i==XN_ROWID ) return "rowid";
  return pIdx->pTable->aCol[i].zName;
}