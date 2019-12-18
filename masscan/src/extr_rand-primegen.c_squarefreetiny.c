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

/* Variables and functions */
 int B ; 
 int* qq60tab ; 
 int* qqtab ; 
 int* two ; 

__attribute__((used)) static void squarefreetiny(register uint32_t *a,uint32_t *Lmodqq,int d)
{
  int j;

  for (j = 0;j < 49;++j) {
    register uint32_t k;
    register uint32_t qq;
    qq = qqtab[j];
    k = qq - 1 - ((Lmodqq[j] + qq60tab[j] * d - 1) % qq);
    while (k < B) {
      register uint32_t pos;
      register uint32_t data;
      register uint32_t bits;
      pos = k;
      data = k;
      pos >>= 5;
      data &= 31;
      k += qq;
      bits = a[pos];
      data = two[data];
      bits |= data;
      a[pos] = bits;
    }
  }
}