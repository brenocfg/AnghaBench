#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sh_mobile_lcdc_chan {int ldmt1r_value; TYPE_1__* cfg; } ;
struct TYPE_2__ {int interface_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int LDMT1R_IFM ; 
#define  RGB12A 145 
#define  RGB12B 144 
#define  RGB16 143 
#define  RGB18 142 
#define  RGB24 141 
#define  RGB8 140 
#define  RGB9 139 
#define  SYS12 138 
#define  SYS16A 137 
#define  SYS16B 136 
#define  SYS16C 135 
#define  SYS18 134 
#define  SYS24 133 
#define  SYS8A 132 
#define  SYS8B 131 
#define  SYS8C 130 
#define  SYS8D 129 
#define  SYS9 128 
 scalar_t__ lcdc_chan_is_sublcd (struct sh_mobile_lcdc_chan*) ; 

__attribute__((used)) static int sh_mobile_lcdc_check_interface(struct sh_mobile_lcdc_chan *ch)
{
	int interface_type = ch->cfg->interface_type;

	switch (interface_type) {
	case RGB8:
	case RGB9:
	case RGB12A:
	case RGB12B:
	case RGB16:
	case RGB18:
	case RGB24:
	case SYS8A:
	case SYS8B:
	case SYS8C:
	case SYS8D:
	case SYS9:
	case SYS12:
	case SYS16A:
	case SYS16B:
	case SYS16C:
	case SYS18:
	case SYS24:
		break;
	default:
		return -EINVAL;
	}

	/* SUBLCD only supports SYS interface */
	if (lcdc_chan_is_sublcd(ch)) {
		if (!(interface_type & LDMT1R_IFM))
			return -EINVAL;

		interface_type &= ~LDMT1R_IFM;
	}

	ch->ldmt1r_value = interface_type;
	return 0;
}