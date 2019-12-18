#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint ;
struct TYPE_4__ {scalar_t__ ndx; TYPE_1__** block; } ;
struct TYPE_3__ {int /*<<< orphan*/ * byte; } ;

/* Variables and functions */
 scalar_t__ DICTIONARY_WINDOW ; 
 int /*<<< orphan*/  UZLIB_DICT_ERROR ; 
 int /*<<< orphan*/  UZLIB_THROW (int /*<<< orphan*/ ) ; 
 scalar_t__ WRITE_BLOCKSIZE ; 
 TYPE_2__* out ; 

uint8_t recall_byte (uint offset) {
  if(offset > DICTIONARY_WINDOW || offset >= out->ndx)
    UZLIB_THROW(UZLIB_DICT_ERROR);
  /* ndx starts at 1. Need relative to 0 */
  uint n   = out->ndx - offset;
  uint pos = n % WRITE_BLOCKSIZE;
  uint blockNo = out->ndx / WRITE_BLOCKSIZE - n  / WRITE_BLOCKSIZE;
  return out->block[blockNo]->byte[pos];
}