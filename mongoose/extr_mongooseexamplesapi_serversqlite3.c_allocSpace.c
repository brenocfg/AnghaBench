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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  EIGHT_BYTE_ALIGNMENT (int /*<<< orphan*/ *) ; 
 int ROUND8 (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *allocSpace(
  void *pBuf,          /* Where return pointer will be stored */
  int nByte,           /* Number of bytes to allocate */
  u8 **ppFrom,         /* IN/OUT: Allocate from *ppFrom */
  u8 *pEnd,            /* Pointer to 1 byte past the end of *ppFrom buffer */
  int *pnByte          /* If allocation cannot be made, increment *pnByte */
){
  assert( EIGHT_BYTE_ALIGNMENT(*ppFrom) );
  if( pBuf ) return pBuf;
  nByte = ROUND8(nByte);
  if( &(*ppFrom)[nByte] <= pEnd ){
    pBuf = (void*)*ppFrom;
    *ppFrom += nByte;
  }else{
    *pnByte += nByte;
  }
  return pBuf;
}