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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  u_char ;
struct uimage_header {scalar_t__ ih_os; scalar_t__ ih_type; int /*<<< orphan*/  ih_magic; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  FW_MAGIC_WNDR3700 137 
#define  FW_MAGIC_WNDR3700V2 136 
#define  FW_MAGIC_WNR1000V2 135 
#define  FW_MAGIC_WNR1000V2_VC 134 
#define  FW_MAGIC_WNR2000V1 133 
#define  FW_MAGIC_WNR2000V3 132 
#define  FW_MAGIC_WNR2000V4 131 
#define  FW_MAGIC_WNR2200 130 
#define  FW_MAGIC_WNR612V2 129 
#define  FW_MAGIC_WPN824N 128 
 scalar_t__ IH_OS_LINUX ; 
 scalar_t__ IH_TYPE_FILESYSTEM ; 
 scalar_t__ IH_TYPE_KERNEL ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t uimage_verify_wndr3700(u_char *buf, size_t len, int *extralen)
{
	struct uimage_header *header = (struct uimage_header *)buf;
	uint8_t expected_type = IH_TYPE_FILESYSTEM;

	switch (be32_to_cpu(header->ih_magic)) {
	case FW_MAGIC_WNR612V2:
	case FW_MAGIC_WNR1000V2:
	case FW_MAGIC_WNR1000V2_VC:
	case FW_MAGIC_WNR2000V1:
	case FW_MAGIC_WNR2000V3:
	case FW_MAGIC_WNR2200:
	case FW_MAGIC_WNDR3700:
	case FW_MAGIC_WNDR3700V2:
	case FW_MAGIC_WPN824N:
		break;
	case FW_MAGIC_WNR2000V4:
		expected_type = IH_TYPE_KERNEL;
		break;
	default:
		return -EINVAL;
	}

	if (header->ih_os != IH_OS_LINUX ||
	    header->ih_type != expected_type)
		return -EINVAL;

	return 0;
}