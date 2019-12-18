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
struct trace_seq {char* buffer; int len; } ;
typedef  unsigned char sector_t ;

/* Variables and functions */
 unsigned char WRITE_SAME ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,unsigned char,...) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
scsi_trace_rw10(struct trace_seq *p, unsigned char *cdb, int len)
{
	const char *ret = p->buffer + p->len;
	sector_t lba = 0, txlen = 0;

	lba |= (cdb[2] << 24);
	lba |= (cdb[3] << 16);
	lba |= (cdb[4] << 8);
	lba |=  cdb[5];
	txlen |= (cdb[7] << 8);
	txlen |=  cdb[8];

	trace_seq_printf(p, "lba=%llu txlen=%llu protect=%u",
			 (unsigned long long)lba, (unsigned long long)txlen,
			 cdb[1] >> 5);

	if (cdb[0] == WRITE_SAME)
		trace_seq_printf(p, " unmap=%u", cdb[1] >> 3 & 1);

	trace_seq_putc(p, 0);
	return ret;
}