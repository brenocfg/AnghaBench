#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int num; scalar_t__* p; int pos; scalar_t__ base; int** buf; int L; } ;
typedef  TYPE_1__ primegen ;

/* Variables and functions */
 int B ; 
 int B32 ; 
 int* pop ; 
 int /*<<< orphan*/  primegen_fill (TYPE_1__*) ; 
 int /*<<< orphan*/  primegen_sieve (TYPE_1__*) ; 

uint64_t primegen_count(primegen *pg,uint64_t to)
{
  uint64_t count = 0;
  
  for (;;) {
    register int pos;
    register int j;
    register uint32_t bits;
    register uint32_t smallcount;
    while (pg->num) {
      if (pg->p[pg->num - 1] >= to) return count;
      ++count;
      --pg->num;
    }

    smallcount = 0;
    pos = pg->pos;
    while ((pos < B32) && (pg->base + 1920 < to)) {
      for (j = 0;j < 16;++j) {
    bits = ~pg->buf[j][pos];
    smallcount += pop[bits & 255]; bits >>= 8;
    smallcount += pop[bits & 255]; bits >>= 8;
    smallcount += pop[bits & 255]; bits >>= 8;
    smallcount += pop[bits & 255];
      }
      pg->base += 1920;
      ++pos;
    }
    pg->pos = pos;
    count += smallcount;

    if (pos == B32)
      while (pg->base + B * 60 < to) {
        primegen_sieve(pg);
        pg->L += B;

    smallcount = 0;
        for (j = 0;j < 16;++j)
      for (pos = 0;pos < B32;++pos) {
        bits = ~pg->buf[j][pos];
        smallcount += pop[bits & 255]; bits >>= 8;
        smallcount += pop[bits & 255]; bits >>= 8;
        smallcount += pop[bits & 255]; bits >>= 8;
        smallcount += pop[bits & 255];
      }
        count += smallcount;
        pg->base += B * 60;
      }

    primegen_fill(pg);
  }
}