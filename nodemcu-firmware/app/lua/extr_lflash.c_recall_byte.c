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
struct TYPE_4__ {unsigned int ndx; TYPE_1__** block; } ;
struct TYPE_3__ {int /*<<< orphan*/ * byte; } ;

/* Variables and functions */
 unsigned int DICTIONARY_WINDOW ; 
 unsigned int WRITE_BLOCKSIZE ; 
 int /*<<< orphan*/  flash_error (char*) ; 
 TYPE_2__* out ; 

__attribute__((used)) static uint8_t recall_byte (unsigned offset) {
  if(offset > DICTIONARY_WINDOW || offset >= out->ndx)
    flash_error("invalid dictionary offset on inflate");
  /* ndx starts at 1. Need relative to 0 */
  unsigned n   = out->ndx - offset;
  unsigned pos = n % WRITE_BLOCKSIZE;
  unsigned blockNo = out->ndx / WRITE_BLOCKSIZE - n  / WRITE_BLOCKSIZE;
  return out->block[blockNo]->byte[pos];
}