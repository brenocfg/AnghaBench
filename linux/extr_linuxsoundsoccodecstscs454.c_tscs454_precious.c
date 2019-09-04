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
struct device {int dummy; } ;

/* Variables and functions */
#define  R_DACCRRDH 145 
#define  R_DACCRRDL 144 
#define  R_DACCRRDM 143 
#define  R_DACCRWDH 142 
#define  R_DACCRWDL 141 
#define  R_DACCRWDM 140 
#define  R_SPKCRRDH 139 
#define  R_SPKCRRDL 138 
#define  R_SPKCRRDM 137 
#define  R_SPKCRWDH 136 
#define  R_SPKCRWDL 135 
#define  R_SPKCRWDM 134 
#define  R_SUBCRRDH 133 
#define  R_SUBCRRDL 132 
#define  R_SUBCRRDM 131 
#define  R_SUBCRWDH 130 
#define  R_SUBCRWDL 129 
#define  R_SUBCRWDM 128 

__attribute__((used)) static bool tscs454_precious(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case R_SPKCRWDL:
	case R_SPKCRWDM:
	case R_SPKCRWDH:
	case R_SPKCRRDL:
	case R_SPKCRRDM:
	case R_SPKCRRDH:

	case R_DACCRWDL:
	case R_DACCRWDM:
	case R_DACCRWDH:
	case R_DACCRRDL:
	case R_DACCRRDM:
	case R_DACCRRDH:

	case R_SUBCRWDL:
	case R_SUBCRWDM:
	case R_SUBCRWDH:
	case R_SUBCRRDL:
	case R_SUBCRRDM:
	case R_SUBCRRDH:
		return true;
	default:
		return false;
	};
}