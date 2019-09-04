#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_3__ {int /*<<< orphan*/  zPType; } ;
struct TYPE_4__ {int flags; char eSubtype; scalar_t__ z; TYPE_1__ u; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 int MEM_Null ; 
 int MEM_Subtype ; 
 int MEM_Term ; 
 int MEM_TypeMask ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

void *sqlite3_value_pointer(sqlite3_value *pVal, const char *zPType){
  Mem *p = (Mem*)pVal;
  if( (p->flags&(MEM_TypeMask|MEM_Term|MEM_Subtype)) ==
                 (MEM_Null|MEM_Term|MEM_Subtype)
   && zPType!=0
   && p->eSubtype=='p'
   && strcmp(p->u.zPType, zPType)==0
  ){
    return (void*)p->z;
  }else{
    return 0;
  }
}