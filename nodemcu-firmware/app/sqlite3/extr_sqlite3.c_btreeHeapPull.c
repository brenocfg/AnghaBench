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
typedef  size_t u32 ;

/* Variables and functions */

__attribute__((used)) static int btreeHeapPull(u32 *aHeap, u32 *pOut){
  u32 j, i, x;
  if( (x = aHeap[0])==0 ) return 0;
  *pOut = aHeap[1];
  aHeap[1] = aHeap[x];
  aHeap[x] = 0xffffffff;
  aHeap[0]--;
  i = 1;
  while( (j = i*2)<=aHeap[0] ){
    if( aHeap[j]>aHeap[j+1] ) j++;
    if( aHeap[i]<aHeap[j] ) break;
    x = aHeap[i];
    aHeap[i] = aHeap[j];
    aHeap[j] = x;
    i = j;
  }
  return 1;
}