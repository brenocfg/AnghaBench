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
struct fw_block {scalar_t__ file_size; int /*<<< orphan*/ * file_name; } ;
struct csum_state {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int write_out_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,struct csum_state*) ; 

int
write_out_block(FILE *outfile, struct fw_block *block, struct csum_state *css)
{
	int res;

	if (block == NULL)
		return 0;

	if (block->file_name == NULL)
		return 0;

	if (block->file_size == 0)
		return 0;

	res = write_out_file(outfile, block->file_name,
			block->file_size, css);
	return res;
}