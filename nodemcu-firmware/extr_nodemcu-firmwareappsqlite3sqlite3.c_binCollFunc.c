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

/* Variables and functions */
 scalar_t__ allSpaces (char*,int) ; 
 int memcmp (void const*,void const*,int) ; 

__attribute__((used)) static int binCollFunc(
  void *padFlag,
  int nKey1, const void *pKey1,
  int nKey2, const void *pKey2
){
  int rc, n;
  n = nKey1<nKey2 ? nKey1 : nKey2;
  /* EVIDENCE-OF: R-65033-28449 The built-in BINARY collation compares
  ** strings byte by byte using the memcmp() function from the standard C
  ** library. */
  rc = memcmp(pKey1, pKey2, n);
  if( rc==0 ){
    if( padFlag
     && allSpaces(((char*)pKey1)+n, nKey1-n)
     && allSpaces(((char*)pKey2)+n, nKey2-n)
    ){
      /* EVIDENCE-OF: R-31624-24737 RTRIM is like BINARY except that extra
      ** spaces at the end of either string do not change the result. In other
      ** words, strings will compare equal to one another as long as they
      ** differ only in the number of spaces at the end.
      */
    }else{
      rc = nKey1 - nKey2;
    }
  }
  return rc;
}