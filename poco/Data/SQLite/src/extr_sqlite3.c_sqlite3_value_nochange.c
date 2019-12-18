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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ sqlite3_value ;

/* Variables and functions */
 int MEM_Null ; 
 int MEM_Zero ; 

int sqlite3_value_nochange(sqlite3_value *pVal){
  return (pVal->flags&(MEM_Null|MEM_Zero))==(MEM_Null|MEM_Zero);
}