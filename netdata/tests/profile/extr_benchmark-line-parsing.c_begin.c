#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct entry {scalar_t__ found; struct entry* next; } ;
struct base {int iteration; scalar_t__ found; struct entry* entries; struct entry* last; scalar_t__ wanted; } ;

/* Variables and functions */
 int unlikely (int) ; 

__attribute__((used)) static inline void begin(struct base *base) {

  if(unlikely(base->iteration % 60) == 1) {
    base->wanted = 0;
    struct entry *e;
    for(e = base->entries; e ; e = e->next)
      if(e->found) base->wanted++;
  }

  base->iteration++;
  base->last = base->entries;
  base->found = 0;
}