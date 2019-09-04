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
struct TYPE_3__ {char* str; scalar_t__ size; scalar_t__ len; } ;
typedef  TYPE_1__ simplestring ;

/* Variables and functions */
 scalar_t__ SIMPLESTRING_INCR ; 
 scalar_t__ emalloc (scalar_t__) ; 

__attribute__((used)) static void simplestring_init_str(simplestring* string) {
   string->str = (char*)emalloc(SIMPLESTRING_INCR);
   if(string->str) {
      string->str[0] = 0;
      string->len = 0;
      string->size = SIMPLESTRING_INCR;
   }
   else {
      string->size = 0;
   }
}