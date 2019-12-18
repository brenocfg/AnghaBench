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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct mylo_partition_header {void* len; void* crc; } ;
struct fw_block {int flags; size_t crc; size_t size; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  ph ;
typedef  int /*<<< orphan*/  buff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
 int BLOCK_FLAG_HAVEHDR ; 
 int FILE_BUF_LEN ; 
 void* HOST_TO_LE32 (size_t) ; 
 int /*<<< orphan*/  dbgmsg (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errmsg (int,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fread (char*,size_t,int,int /*<<< orphan*/ *) ; 
 scalar_t__ get_file_crc (struct fw_block*) ; 
 scalar_t__ write_out_data (int /*<<< orphan*/ *,char*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ write_out_padding (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ *) ; 

int
write_out_file(FILE *outfile, struct fw_block *block, uint32_t *crc)
{
	char buff[FILE_BUF_LEN];
	size_t  buflen = sizeof(buff);
	FILE *f;
	size_t len;

	errno = 0;

	if (block->name == NULL) {
		return 0;
	}

	if ((block->flags & BLOCK_FLAG_HAVEHDR) != 0) {
		struct mylo_partition_header ph;

		if (get_file_crc(block) != 0)
		        return -1;

		ph.crc = HOST_TO_LE32(block->crc);
		ph.len = HOST_TO_LE32(block->size);

		if (write_out_data(outfile, (uint8_t *)&ph, sizeof(ph), crc) != 0)
			return -1;
	}

	f = fopen(block->name,"r");
	if (errno) {
		errmsg(1,"unable to open file: %s", block->name);
		return -1;
	}

	len = block->size;
	while (len > 0) {
		if (len < buflen)
			buflen = len;

		/* read data from source file */
		errno = 0;
		fread(buff, buflen, 1, f);
		if (errno != 0) {
			errmsg(1,"unable to read from file: %s",block->name);
			return -1;
		}

		if (write_out_data(outfile, buff, buflen, crc) != 0)
			return -1;

		len -= buflen;
	}

	fclose(f);

	/* align next block on a 4 byte boundary */
	len = ALIGN(len,4) - block->size;
	if (write_out_padding(outfile, len, 0xFF, crc))
		return -1;

	dbgmsg(1,"file %s written out", block->name);
	return 0;
}