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
struct csys_block {int /*<<< orphan*/  size_csum; struct csum_state* css; int /*<<< orphan*/  size_avail; int /*<<< orphan*/  file_size; int /*<<< orphan*/  file_name; } ;
struct csum_state {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int block_writeout_csum (int /*<<< orphan*/ *,struct csys_block*) ; 
 int block_writeout_data (int /*<<< orphan*/ *,struct csys_block*) ; 
 int block_writeout_hdr (int /*<<< orphan*/ *,struct csys_block*) ; 
 int /*<<< orphan*/  csum_init (struct csum_state*,int /*<<< orphan*/ ) ; 

int
block_writeout(FILE *outfile, struct csys_block *block)
{
	int res;
	struct csum_state css;

	res = 0;

	if (block == NULL)
		return res;

	block->css = NULL;

	DBG(2, "writing block, file=%s, file_size=%d, space=%d",
		block->file_name, block->file_size, block->size_avail);
	res = block_writeout_hdr(outfile, block);
	if (res)
		return res;

	if (block->size_csum != 0) {
		block->css = &css;
		csum_init(&css, block->size_csum);
	}

	res = block_writeout_data(outfile, block);
	if (res)
		return res;

	res = block_writeout_csum(outfile, block);
	if (res)
		return res;

	return res;
}