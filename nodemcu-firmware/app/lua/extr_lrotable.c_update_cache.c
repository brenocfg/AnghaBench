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
struct TYPE_3__ {unsigned int member_0; size_t member_1; unsigned int member_2; unsigned int hash; size_t addr; unsigned int ndx; } ;
typedef  TYPE_1__ cache_line_t ;
typedef  int /*<<< orphan*/  ROTable ;

/* Variables and functions */
 int /*<<< orphan*/  COUNT (int) ; 
 int LA_LINES ; 
 int LA_SLOTS ; 
 TYPE_1__** cache ; 

__attribute__((used)) static void update_cache(unsigned hash, ROTable *rotable, unsigned ndx) {
  int i = (hash)>>2 & (LA_LINES-1), j;
#ifndef _MSC_VER
  cache_line_t cl = {hash, (size_t) rotable, ndx};
#else
  cache_line_t cl;             // MSC doesn't allow non-scalar initialisers, which
  cl.hash = hash;              // is a pity because xtensa gcc generates optimum   
  cl.addr = (size_t) rotable;  // code using them.
  cl.ndx  = ndx;
#endif

  COUNT(2);
  if (ndx>0xffu)
    return;
  for (j = LA_SLOTS-1; j>0; j--)
    cache[i][j] = cache[i][j-1];
  cache[i][0] = cl;
}