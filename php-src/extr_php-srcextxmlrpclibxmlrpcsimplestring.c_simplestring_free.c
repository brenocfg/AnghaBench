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
struct TYPE_3__ {scalar_t__ len; scalar_t__ str; } ;
typedef  TYPE_1__ simplestring ;

/* Variables and functions */
 int /*<<< orphan*/  my_free (scalar_t__) ; 

void simplestring_free(simplestring* string) {
   if(string && string->str) {
      my_free(string->str);
      string->len = 0;
   }
}