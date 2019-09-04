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
#define  READ_32 131 
 int SERVICE_ACTION32 (unsigned char*) ; 
#define  VERIFY_32 130 
#define  WRITE_32 129 
#define  WRITE_SAME_32 128 
 char const* scsi_trace_misc (struct trace_seq*,unsigned char*,int) ; 
 char const* scsi_trace_rw32 (struct trace_seq*,unsigned char*,int) ; 

__attribute__((used)) static const char *
scsi_trace_varlen(struct trace_seq *p, unsigned char *cdb, int len)
{
	switch (SERVICE_ACTION32(cdb)) {
	case READ_32:
	case VERIFY_32:
	case WRITE_32:
	case WRITE_SAME_32:
		return scsi_trace_rw32(p, cdb, len);
	default:
		return scsi_trace_misc(p, cdb, len);
	}
}