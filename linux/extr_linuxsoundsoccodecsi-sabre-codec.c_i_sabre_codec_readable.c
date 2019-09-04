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
#define  ISABRECODEC_REG_01 134 
#define  ISABRECODEC_REG_02 133 
#define  ISABRECODEC_REG_10 132 
#define  ISABRECODEC_REG_20 131 
#define  ISABRECODEC_REG_21 130 
#define  ISABRECODEC_REG_22 129 
#define  ISABRECODEC_REG_24 128 

__attribute__((used)) static bool i_sabre_codec_readable(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case ISABRECODEC_REG_01:
	case ISABRECODEC_REG_02:
	case ISABRECODEC_REG_10:
	case ISABRECODEC_REG_20:
	case ISABRECODEC_REG_21:
	case ISABRECODEC_REG_22:
	case ISABRECODEC_REG_24:
		return true;

	default:
		return false;
	}
}