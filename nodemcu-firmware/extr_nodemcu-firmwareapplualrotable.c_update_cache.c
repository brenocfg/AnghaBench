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
struct TYPE_2__ {unsigned int hash; size_t addr; unsigned int ndx; } ;
typedef  int /*<<< orphan*/  ROTable ;

/* Variables and functions */
 int /*<<< orphan*/  COUNT (int) ; 
 int LA_LINES ; 
 int LA_SLOTS ; 
 TYPE_1__** cache ; 

__attribute__((used)) static void update_cache(unsigned hash, ROTable *rotable, unsigned ndx) {
  int i = (hash)>>2 & (LA_LINES-1), j;
  COUNT(2);
  if (ndx>0xffu)
    return;
  for (j = LA_SLOTS-1; j>0; j--)
    cache[i][j] = cache[i][j-1];
  cache[i][0].hash = hash;
  cache[i][0].addr = (size_t) rotable;
  cache[i][0].ndx  = ndx;
}