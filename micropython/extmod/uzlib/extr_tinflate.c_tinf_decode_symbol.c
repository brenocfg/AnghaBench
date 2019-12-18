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
struct TYPE_3__ {int* table; int* trans; } ;
typedef  TYPE_1__ TINF_TREE ;
typedef  int /*<<< orphan*/  TINF_DATA ;

/* Variables and functions */
 int TINF_ARRAY_SIZE (int*) ; 
 int TINF_DATA_ERROR ; 
 int tinf_getbit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tinf_decode_symbol(TINF_DATA *d, TINF_TREE *t)
{
   int sum = 0, cur = 0, len = 0;

   /* get more bits while code value is above sum */
   do {

      cur = 2*cur + tinf_getbit(d);

      if (++len == TINF_ARRAY_SIZE(t->table)) {
         return TINF_DATA_ERROR;
      }

      sum += t->table[len];
      cur -= t->table[len];

   } while (cur >= 0);

   sum += cur;
   #if UZLIB_CONF_PARANOID_CHECKS
   if (sum < 0 || sum >= TINF_ARRAY_SIZE(t->trans)) {
      return TINF_DATA_ERROR;
   }
   #endif

   return t->trans[sum];
}