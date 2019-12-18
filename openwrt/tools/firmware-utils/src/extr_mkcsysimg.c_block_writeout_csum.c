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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct csys_block {int /*<<< orphan*/  size_csum; int /*<<< orphan*/  css; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 int /*<<< orphan*/  HOST_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_get (int /*<<< orphan*/ ) ; 
 int write_out_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
block_writeout_csum(FILE *outfile, struct csys_block *block)
{
	uint16_t csum;
	int res;

	if (block->size_csum == 0)
		return 0;

	DBG(1,"writing checksum for block");
	csum = HOST_TO_LE16(csum_get(block->css));
	res = write_out_data(outfile, (uint8_t *)&csum, block->size_csum, NULL);

	return res;
}