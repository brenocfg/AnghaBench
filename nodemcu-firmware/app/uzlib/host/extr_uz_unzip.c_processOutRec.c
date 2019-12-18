#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ndx; scalar_t__ written; scalar_t__ len; int /*<<< orphan*/ * fullBlkCB; int /*<<< orphan*/  fout; int /*<<< orphan*/  crc; int /*<<< orphan*/ * block; } ;

/* Variables and functions */
 int /*<<< orphan*/  UZLIB_DATA_ERROR ; 
 int /*<<< orphan*/  UZLIB_THROW (int /*<<< orphan*/ ) ; 
 int WRITE_BLOCKSIZE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int fwrite (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* out ; 
 int /*<<< orphan*/  uzlib_crc32 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int processOutRec (void) {
  int len = (out->ndx % WRITE_BLOCKSIZE) ? out->ndx % WRITE_BLOCKSIZE :
                                           WRITE_BLOCKSIZE;
  if (fwrite(out->block[0], 1, len, out->fout) != len)
    UZLIB_THROW(UZLIB_DATA_ERROR);

  out->crc = uzlib_crc32(out->block[0], len, out->crc);

  out->written += len;
  if (out->written == out->len) {
    fclose(out->fout);
    out->fullBlkCB = NULL;
  }
  return 1;
}