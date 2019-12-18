#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_2__ {int flags; unsigned int eSubtype; } ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */
 int MEM_Subtype ; 

unsigned int sqlite3_value_subtype(sqlite3_value *pVal){
  Mem *pMem = (Mem*)pVal;
  return ((pMem->flags & MEM_Subtype) ? pMem->eSubtype : 0);
}