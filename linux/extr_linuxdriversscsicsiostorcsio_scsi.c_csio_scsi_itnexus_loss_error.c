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
typedef  int uint16_t ;

/* Variables and functions */
#define  FW_ERR_LINK_DOWN 132 
#define  FW_ERR_RDEV_IMPL_LOGO 131 
#define  FW_ERR_RDEV_LOGO 130 
#define  FW_ERR_RDEV_LOST 129 
#define  FW_RDEV_NOT_READY 128 

__attribute__((used)) static inline bool
csio_scsi_itnexus_loss_error(uint16_t error)
{
	switch (error) {
	case FW_ERR_LINK_DOWN:
	case FW_RDEV_NOT_READY:
	case FW_ERR_RDEV_LOST:
	case FW_ERR_RDEV_LOGO:
	case FW_ERR_RDEV_IMPL_LOGO:
		return 1;
	}
	return 0;
}