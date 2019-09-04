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
typedef  int u8 ;

/* Variables and functions */
 int EAGAIN ; 
 int EILSEQ ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 int EMSGSIZE ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ETIMEDOUT ; 
#define  GB_OP_INTERRUPTED 138 
#define  GB_OP_INVALID 137 
#define  GB_OP_MALFUNCTION 136 
#define  GB_OP_NONEXISTENT 135 
#define  GB_OP_NO_MEMORY 134 
#define  GB_OP_OVERFLOW 133 
#define  GB_OP_PROTOCOL_BAD 132 
#define  GB_OP_RETRY 131 
#define  GB_OP_SUCCESS 130 
#define  GB_OP_TIMEOUT 129 
#define  GB_OP_UNKNOWN_ERROR 128 

__attribute__((used)) static int gb_operation_status_map(u8 status)
{
	switch (status) {
	case GB_OP_SUCCESS:
		return 0;
	case GB_OP_INTERRUPTED:
		return -EINTR;
	case GB_OP_TIMEOUT:
		return -ETIMEDOUT;
	case GB_OP_NO_MEMORY:
		return -ENOMEM;
	case GB_OP_PROTOCOL_BAD:
		return -EPROTONOSUPPORT;
	case GB_OP_OVERFLOW:
		return -EMSGSIZE;
	case GB_OP_INVALID:
		return -EINVAL;
	case GB_OP_RETRY:
		return -EAGAIN;
	case GB_OP_NONEXISTENT:
		return -ENODEV;
	case GB_OP_MALFUNCTION:
		return -EILSEQ;
	case GB_OP_UNKNOWN_ERROR:
	default:
		return -EIO;
	}
}