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
struct csys_header {void* size; void* addr; int /*<<< orphan*/  sig; } ;
struct csys_block {scalar_t__ size_hdr; scalar_t__ addr; scalar_t__ size; scalar_t__ size_csum; int /*<<< orphan*/  sig; } ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*) ; 
 void* HOST_TO_LE32 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int write_out_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
block_writeout_hdr(FILE *outfile, struct csys_block *block)
{
	struct csys_header hdr;
	int res;

	if (block->size_hdr == 0)
		return 0;

	/* setup header fields */
	memcpy(hdr.sig, block->sig, 4);
	hdr.addr = HOST_TO_LE32(block->addr);
	hdr.size = HOST_TO_LE32(block->size - block->size_hdr - block->size_csum);

	DBG(1,"writing header for block");
	res = write_out_data(outfile, (uint8_t *)&hdr, sizeof(hdr),NULL);
	return res;

}