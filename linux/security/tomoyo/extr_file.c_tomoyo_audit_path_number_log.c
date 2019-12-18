#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int operation; TYPE_1__* filename; int /*<<< orphan*/  number; } ;
struct TYPE_6__ {TYPE_2__ path_number; } ;
struct tomoyo_request_info {TYPE_3__ param; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  TOMOYO_TYPE_CHMOD 133 
#define  TOMOYO_TYPE_CREATE 132 
#define  TOMOYO_TYPE_IOCTL 131 
#define  TOMOYO_TYPE_MKDIR 130 
#define  TOMOYO_TYPE_MKFIFO 129 
#define  TOMOYO_TYPE_MKSOCK 128 
 int TOMOYO_VALUE_TYPE_DECIMAL ; 
 int TOMOYO_VALUE_TYPE_HEXADECIMAL ; 
 int TOMOYO_VALUE_TYPE_OCTAL ; 
 int /*<<< orphan*/ * tomoyo_mac_keywords ; 
 size_t* tomoyo_pn2mac ; 
 int /*<<< orphan*/  tomoyo_print_ulong (char*,int,int /*<<< orphan*/ ,int) ; 
 int tomoyo_supervisor (struct tomoyo_request_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tomoyo_audit_path_number_log(struct tomoyo_request_info *r)
{
	const u8 type = r->param.path_number.operation;
	u8 radix;
	char buffer[64];

	switch (type) {
	case TOMOYO_TYPE_CREATE:
	case TOMOYO_TYPE_MKDIR:
	case TOMOYO_TYPE_MKFIFO:
	case TOMOYO_TYPE_MKSOCK:
	case TOMOYO_TYPE_CHMOD:
		radix = TOMOYO_VALUE_TYPE_OCTAL;
		break;
	case TOMOYO_TYPE_IOCTL:
		radix = TOMOYO_VALUE_TYPE_HEXADECIMAL;
		break;
	default:
		radix = TOMOYO_VALUE_TYPE_DECIMAL;
		break;
	}
	tomoyo_print_ulong(buffer, sizeof(buffer), r->param.path_number.number,
			   radix);
	return tomoyo_supervisor(r, "file %s %s %s\n", tomoyo_mac_keywords
				 [tomoyo_pn2mac[type]],
				 r->param.path_number.filename->name, buffer);
}