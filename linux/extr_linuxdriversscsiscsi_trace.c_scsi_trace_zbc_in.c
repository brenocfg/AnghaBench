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
typedef  unsigned char u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct trace_seq {int dummy; } ;

/* Variables and functions */
 int SERVICE_ACTION16 (unsigned char*) ; 
#define  ZI_REPORT_ZONES 128 
 int /*<<< orphan*/  get_unaligned_be32 (unsigned char*) ; 
 scalar_t__ get_unaligned_be64 (unsigned char*) ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char const*,unsigned long long,int /*<<< orphan*/ ,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

__attribute__((used)) static const char *
scsi_trace_zbc_in(struct trace_seq *p, unsigned char *cdb, int len)
{
	const char *ret = trace_seq_buffer_ptr(p), *cmd;
	u64 zone_id;
	u32 alloc_len;
	u8 options;

	switch (SERVICE_ACTION16(cdb)) {
	case ZI_REPORT_ZONES:
		cmd = "REPORT_ZONES";
		break;
	default:
		trace_seq_puts(p, "UNKNOWN");
		goto out;
	}

	zone_id = get_unaligned_be64(&cdb[2]);
	alloc_len = get_unaligned_be32(&cdb[10]);
	options = cdb[14] & 0x3f;

	trace_seq_printf(p, "%s zone=%llu alloc_len=%u options=%u partial=%u",
			 cmd, (unsigned long long)zone_id, alloc_len,
			 options, (cdb[14] >> 7) & 1);

out:
	trace_seq_putc(p, 0);

	return ret;
}