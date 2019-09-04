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
typedef  int /*<<< orphan*/  u32 ;
struct trace_seq {int dummy; } ;

/* Variables and functions */
#define  MO_CHANGE_ALIASES 133 
#define  MO_MANAGEMENT_PROTOCOL_OUT 132 
#define  MO_SET_IDENTIFYING_INFORMATION 131 
#define  MO_SET_PRIORITY 130 
#define  MO_SET_TARGET_PGS 129 
#define  MO_SET_TIMESTAMP 128 
 int SERVICE_ACTION16 (unsigned char*) ; 
 int /*<<< orphan*/  get_unaligned_be32 (unsigned char*) ; 
 char* trace_seq_buffer_ptr (struct trace_seq*) ; 
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,char*) ; 

__attribute__((used)) static const char *
scsi_trace_maintenance_out(struct trace_seq *p, unsigned char *cdb, int len)
{
	const char *ret = trace_seq_buffer_ptr(p), *cmd;
	u32 alloc_len;

	switch (SERVICE_ACTION16(cdb)) {
	case MO_SET_IDENTIFYING_INFORMATION:
		cmd = "SET_IDENTIFYING_INFORMATION";
		break;
	case MO_SET_TARGET_PGS:
		cmd = "SET_TARGET_PORT_GROUPS";
		break;
	case MO_CHANGE_ALIASES:
		cmd = "CHANGE_ALIASES";
		break;
	case MO_SET_PRIORITY:
		cmd = "SET_PRIORITY";
		break;
	case MO_SET_TIMESTAMP:
		cmd = "SET_TIMESTAMP";
		break;
	case MO_MANAGEMENT_PROTOCOL_OUT:
		cmd = "MANAGEMENT_PROTOCOL_OUT";
		break;
	default:
		trace_seq_puts(p, "UNKNOWN");
		goto out;
	}

	alloc_len = get_unaligned_be32(&cdb[6]);

	trace_seq_printf(p, "%s alloc_len=%u", cmd, alloc_len);

out:
	trace_seq_putc(p, 0);

	return ret;
}