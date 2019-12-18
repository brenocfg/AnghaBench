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
typedef  int uint32_t ;
typedef  int int64_t ;

/* Variables and functions */
 long B ; 
 int* two ; 

__attribute__((used)) static void doit12(register uint32_t *a,register long x,register long y,int64_t start)
{
  register long i;
  register uint32_t data;
  register uint32_t bits;

  x += 5;

  start += 1000000000;
  while (start < 0) { start += x; x += 10; }
  start -= 1000000000;
  i = start;
  while (i < 0) { i += x; x += 10; }

  y += 15;
  x += 10;

  for (;;) {
    long i0;
    long y0;
    while (i >= B) {
      if (x <= y) return;
      i -= y;
      y += 30;
    }
    i0 = i;
    y0 = y;
    while ((i >= 0) && (y < x)) {
      register uint32_t pos;
      pos = (uint32_t)i; data = (uint32_t)i;
      pos >>= 5; data &= 31;
      i -= y;
      y += 30;
      bits = a[pos]; data = two[data];
      bits ^= data;
      a[pos] = bits;
    }
    i = i0;
    y = y0;
    i += x - 10;
    x += 10;
  }
}