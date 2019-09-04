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
struct TYPE_3__ {unsigned int* trans; scalar_t__* table; } ;
typedef  TYPE_1__ TINF_TREE ;

/* Variables and functions */

__attribute__((used)) static void tinf_build_tree(TINF_TREE *t, const unsigned char *lengths, unsigned int num)
{
   unsigned short offs[16];
   unsigned int i, sum;

   /* clear code length count table */
   for (i = 0; i < 16; ++i) t->table[i] = 0;

   /* scan symbol lengths, and sum code length counts */
   for (i = 0; i < num; ++i) t->table[lengths[i]]++;

   #if UZLIB_CONF_DEBUG_LOG >= 2
   UZLIB_DUMP_ARRAY("codelen counts:", t->table, TINF_ARRAY_SIZE(t->table));
   #endif

   /* In the lengths array, 0 means unused code. So, t->table[0] now contains
      number of unused codes. But table's purpose is to contain # of codes of
      particular length, and there're 0 codes of length 0. */
   t->table[0] = 0;

   /* compute offset table for distribution sort */
   for (sum = 0, i = 0; i < 16; ++i)
   {
      offs[i] = sum;
      sum += t->table[i];
   }

   #if UZLIB_CONF_DEBUG_LOG >= 2
   UZLIB_DUMP_ARRAY("codelen offsets:", offs, TINF_ARRAY_SIZE(offs));
   #endif

   /* create code->symbol translation table (symbols sorted by code) */
   for (i = 0; i < num; ++i)
   {
      if (lengths[i]) t->trans[offs[lengths[i]]++] = i;
   }
}