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
typedef  enum amic_micbias { ____Placeholder_amic_micbias } amic_micbias ;

/* Variables and functions */
#define  AMIC_MICBIAS_VAMIC1 129 
#define  AMIC_MICBIAS_VAMIC2 128 

__attribute__((used)) static inline const char *amic_micbias_str(enum amic_micbias micbias)
{
	switch (micbias) {
	case AMIC_MICBIAS_VAMIC1:
		return "VAMIC1";
	case AMIC_MICBIAS_VAMIC2:
		return "VAMIC2";
	default:
		return "Unknown";
	}
}