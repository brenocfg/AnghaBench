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
#define  PCM186X_CLK_STATUS 135 
#define  PCM186X_DEVICE_STATUS 134 
#define  PCM186X_DIV_STATUS 133 
#define  PCM186X_FSAMPLE_STATUS 132 
#define  PCM186X_MMAP_ADDRESS 131 
#define  PCM186X_MMAP_STAT_CTRL 130 
#define  PCM186X_PAGE 129 
#define  PCM186X_SUPPLY_STATUS 128 

__attribute__((used)) static bool pcm186x_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case PCM186X_PAGE:
	case PCM186X_DEVICE_STATUS:
	case PCM186X_FSAMPLE_STATUS:
	case PCM186X_DIV_STATUS:
	case PCM186X_CLK_STATUS:
	case PCM186X_SUPPLY_STATUS:
	case PCM186X_MMAP_STAT_CTRL:
	case PCM186X_MMAP_ADDRESS:
		return true;
	}

	return false;
}