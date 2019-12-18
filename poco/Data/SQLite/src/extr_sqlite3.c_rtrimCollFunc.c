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
typedef  char u8 ;

/* Variables and functions */
 int binCollFunc (void*,int,void const*,int,void const*) ; 

__attribute__((used)) static int rtrimCollFunc(
  void *pUser,
  int nKey1, const void *pKey1,
  int nKey2, const void *pKey2
){
  const u8 *pK1 = (const u8*)pKey1;
  const u8 *pK2 = (const u8*)pKey2;
  while( nKey1 && pK1[nKey1-1]==' ' ) nKey1--;
  while( nKey2 && pK2[nKey2-1]==' ' ) nKey2--;
  return binCollFunc(pUser, nKey1, pKey1, nKey2, pKey2);
}