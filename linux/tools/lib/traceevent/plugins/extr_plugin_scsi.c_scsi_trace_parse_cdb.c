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
struct trace_seq {int dummy; } ;

/* Variables and functions */
#define  READ_10 143 
#define  READ_12 142 
#define  READ_16 141 
#define  READ_6 140 
#define  SERVICE_ACTION_IN_16 139 
#define  UNMAP 138 
#define  VARIABLE_LENGTH_CMD 137 
#define  VERIFY 136 
#define  VERIFY_12 135 
#define  VERIFY_16 134 
#define  WRITE_10 133 
#define  WRITE_12 132 
#define  WRITE_16 131 
#define  WRITE_6 130 
#define  WRITE_SAME 129 
#define  WRITE_SAME_16 128 
 char const* scsi_trace_misc (struct trace_seq*,unsigned char*,int) ; 
 char const* scsi_trace_rw10 (struct trace_seq*,unsigned char*,int) ; 
 char const* scsi_trace_rw12 (struct trace_seq*,unsigned char*,int) ; 
 char const* scsi_trace_rw16 (struct trace_seq*,unsigned char*,int) ; 
 char const* scsi_trace_rw6 (struct trace_seq*,unsigned char*,int) ; 
 char const* scsi_trace_service_action_in (struct trace_seq*,unsigned char*,int) ; 
 char const* scsi_trace_unmap (struct trace_seq*,unsigned char*,int) ; 
 char const* scsi_trace_varlen (struct trace_seq*,unsigned char*,int) ; 

const char *
scsi_trace_parse_cdb(struct trace_seq *p, unsigned char *cdb, int len)
{
	switch (cdb[0]) {
	case READ_6:
	case WRITE_6:
		return scsi_trace_rw6(p, cdb, len);
	case READ_10:
	case VERIFY:
	case WRITE_10:
	case WRITE_SAME:
		return scsi_trace_rw10(p, cdb, len);
	case READ_12:
	case VERIFY_12:
	case WRITE_12:
		return scsi_trace_rw12(p, cdb, len);
	case READ_16:
	case VERIFY_16:
	case WRITE_16:
	case WRITE_SAME_16:
		return scsi_trace_rw16(p, cdb, len);
	case UNMAP:
		return scsi_trace_unmap(p, cdb, len);
	case SERVICE_ACTION_IN_16:
		return scsi_trace_service_action_in(p, cdb, len);
	case VARIABLE_LENGTH_CMD:
		return scsi_trace_varlen(p, cdb, len);
	default:
		return scsi_trace_misc(p, cdb, len);
	}
}