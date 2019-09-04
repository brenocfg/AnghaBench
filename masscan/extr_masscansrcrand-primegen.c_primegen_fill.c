#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int pos; int** buf; scalar_t__ num; void** p; void* base; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ primegen ;

/* Variables and functions */
 scalar_t__ B ; 
 int B32 ; 
 int /*<<< orphan*/  primegen_sieve (TYPE_1__*) ; 

void primegen_fill(primegen *pg)
{
  int i;
  uint32_t mask;
  uint32_t bits0, bits1, bits2, bits3, bits4, bits5, bits6, bits7;
  uint32_t bits8, bits9, bits10, bits11, bits12, bits13, bits14, bits15;
  uint64_t base;

  i = pg->pos;
  if (i == B32) {
    primegen_sieve(pg);
    pg->L += B;
    i = 0;
  }
  pg->pos = i + 1;

  bits0 = ~pg->buf[0][i];
  bits1 = ~pg->buf[1][i];
  bits2 = ~pg->buf[2][i];
  bits3 = ~pg->buf[3][i];
  bits4 = ~pg->buf[4][i];
  bits5 = ~pg->buf[5][i];
  bits6 = ~pg->buf[6][i];
  bits7 = ~pg->buf[7][i];
  bits8 = ~pg->buf[8][i];
  bits9 = ~pg->buf[9][i];
  bits10 = ~pg->buf[10][i];
  bits11 = ~pg->buf[11][i];
  bits12 = ~pg->buf[12][i];
  bits13 = ~pg->buf[13][i];
  bits14 = ~pg->buf[14][i];
  bits15 = ~pg->buf[15][i];

  base = pg->base + 1920;
  pg->base = base;

  pg->num = 0;

  for (mask = 0x80000000;mask;mask >>= 1) {
    base -= 60;
    if (bits15 & mask) pg->p[pg->num++] = base + 59;
    if (bits14 & mask) pg->p[pg->num++] = base + 53;
    if (bits13 & mask) pg->p[pg->num++] = base + 49;
    if (bits12 & mask) pg->p[pg->num++] = base + 47;
    if (bits11 & mask) pg->p[pg->num++] = base + 43;
    if (bits10 & mask) pg->p[pg->num++] = base + 41;
    if (bits9 & mask) pg->p[pg->num++] = base + 37;
    if (bits8 & mask) pg->p[pg->num++] = base + 31;
    if (bits7 & mask) pg->p[pg->num++] = base + 29;
    if (bits6 & mask) pg->p[pg->num++] = base + 23;
    if (bits5 & mask) pg->p[pg->num++] = base + 19;
    if (bits4 & mask) pg->p[pg->num++] = base + 17;
    if (bits3 & mask) pg->p[pg->num++] = base + 13;
    if (bits2 & mask) pg->p[pg->num++] = base + 11;
    if (bits1 & mask) pg->p[pg->num++] = base + 7;
    if (bits0 & mask) pg->p[pg->num++] = base + 1;
  }
}