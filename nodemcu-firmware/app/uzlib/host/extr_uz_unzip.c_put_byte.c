#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * byte; } ;
typedef  TYPE_1__ outBlock ;
struct TYPE_6__ {int ndx; int len; TYPE_1__** block; int /*<<< orphan*/  (* fullBlkCB ) () ;} ;

/* Variables and functions */
 int WRITE_BLOCKS ; 
 int WRITE_BLOCKSIZE ; 
 int /*<<< orphan*/  memmove (TYPE_1__**,TYPE_1__**,int) ; 
 TYPE_2__* out ; 
 int /*<<< orphan*/  stub1 () ; 

void put_byte (uint8_t value) {
  int offset = out->ndx % WRITE_BLOCKSIZE;  /* counts from 0 */

  out->block[0]->byte[offset++] = value;
  out->ndx++;

  if (offset == WRITE_BLOCKSIZE || out->ndx == out->len) {
    if (out->fullBlkCB)
      out->fullBlkCB();
    /* circular shift the block pointers (redundant on last block, but so what) */
    outBlock *nextBlock  = out->block[WRITE_BLOCKS - 1];
    memmove(out->block+1, out->block, (WRITE_BLOCKS-1)*sizeof(void*));
    out->block[0] = nextBlock;
  }
}