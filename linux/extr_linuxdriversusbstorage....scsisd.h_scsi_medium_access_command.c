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
struct scsi_cmnd {int* cmnd; } ;

/* Variables and functions */
#define  READ_10 147 
#define  READ_12 146 
#define  READ_16 145 
#define  READ_32 144 
#define  READ_6 143 
#define  SYNCHRONIZE_CACHE 142 
#define  UNMAP 141 
#define  VARIABLE_LENGTH_CMD 140 
#define  VERIFY 139 
#define  VERIFY_12 138 
#define  VERIFY_16 137 
#define  VERIFY_32 136 
#define  WRITE_10 135 
#define  WRITE_12 134 
#define  WRITE_16 133 
#define  WRITE_32 132 
#define  WRITE_6 131 
#define  WRITE_SAME 130 
#define  WRITE_SAME_16 129 
#define  WRITE_SAME_32 128 

__attribute__((used)) static inline int scsi_medium_access_command(struct scsi_cmnd *scmd)
{
	switch (scmd->cmnd[0]) {
	case READ_6:
	case READ_10:
	case READ_12:
	case READ_16:
	case SYNCHRONIZE_CACHE:
	case VERIFY:
	case VERIFY_12:
	case VERIFY_16:
	case WRITE_6:
	case WRITE_10:
	case WRITE_12:
	case WRITE_16:
	case WRITE_SAME:
	case WRITE_SAME_16:
	case UNMAP:
		return 1;
	case VARIABLE_LENGTH_CMD:
		switch (scmd->cmnd[9]) {
		case READ_32:
		case VERIFY_32:
		case WRITE_32:
		case WRITE_SAME_32:
			return 1;
		}
	}

	return 0;
}