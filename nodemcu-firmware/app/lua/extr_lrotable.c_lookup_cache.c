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
struct TYPE_3__ {unsigned int hash; size_t addr; int ndx; } ;
typedef  TYPE_1__ cache_line_t ;
typedef  int /*<<< orphan*/  ROTable ;

/* Variables and functions */
 int /*<<< orphan*/  COUNT (int) ; 
 int LA_LINES ; 
 int LA_SLOTS ; 
 TYPE_1__** cache ; 

__attribute__((used)) static int lookup_cache(unsigned hash, ROTable *rotable) {
  int i = (hash>>2) & (LA_LINES-1), j;

  for (j = 0; j<LA_SLOTS; j++) {
    cache_line_t cl = cache[i][j];
    if (cl.hash == hash && ((size_t)rotable & 0xffffffu) == cl.addr) {
      COUNT(0);
      return cl.ndx;
    }
  }
  COUNT(1);
  return -1;
}