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
#define  R_DACCRWDH 136 
#define  R_DACCRWDL 135 
#define  R_DACCRWDM 134 
#define  R_SPKCRWDH 133 
#define  R_SPKCRWDL 132 
#define  R_SPKCRWDM 131 
#define  R_SUBCRWDH 130 
#define  R_SUBCRWDL 129 
#define  R_SUBCRWDM 128 

__attribute__((used)) static bool tscs454_readable(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case R_SPKCRWDL:
	case R_SPKCRWDM:
	case R_SPKCRWDH:

	case R_DACCRWDL:
	case R_DACCRWDM:
	case R_DACCRWDH:

	case R_SUBCRWDL:
	case R_SUBCRWDM:
	case R_SUBCRWDH:
		return false;
	default:
		return true;
	};
}