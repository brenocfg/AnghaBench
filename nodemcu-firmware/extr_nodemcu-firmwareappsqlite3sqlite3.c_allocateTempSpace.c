#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pTmpSpace; int /*<<< orphan*/  pageSize; } ;
typedef  TYPE_1__ BtShared ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3PageMalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void allocateTempSpace(BtShared *pBt){
  if( !pBt->pTmpSpace ){
    pBt->pTmpSpace = sqlite3PageMalloc( pBt->pageSize );

    /* One of the uses of pBt->pTmpSpace is to format cells before
    ** inserting them into a leaf page (function fillInCell()). If
    ** a cell is less than 4 bytes in size, it is rounded up to 4 bytes
    ** by the various routines that manipulate binary cells. Which
    ** can mean that fillInCell() only initializes the first 2 or 3
    ** bytes of pTmpSpace, but that the first 4 bytes are copied from
    ** it into a database page. This is not actually a problem, but it
    ** does cause a valgrind error when the 1 or 2 bytes of unitialized
    ** data is passed to system call write(). So to avoid this error,
    ** zero the first 4 bytes of temp space here.
    **
    ** Also:  Provide four bytes of initialized space before the
    ** beginning of pTmpSpace as an area available to prepend the
    ** left-child pointer to the beginning of a cell.
    */
    if( pBt->pTmpSpace ){
      memset(pBt->pTmpSpace, 0, 8);
      pBt->pTmpSpace += 4;
    }
  }
}