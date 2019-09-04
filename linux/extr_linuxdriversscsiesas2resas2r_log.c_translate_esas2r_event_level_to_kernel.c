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

/* Variables and functions */
#define  ESAS2R_LOG_CRIT 132 
#define  ESAS2R_LOG_DEBG 131 
#define  ESAS2R_LOG_INFO 130 
#define  ESAS2R_LOG_TRCE 129 
#define  ESAS2R_LOG_WARN 128 
 char const* KERN_CRIT ; 
 char const* KERN_DEBUG ; 
 char const* KERN_INFO ; 
 char const* KERN_WARNING ; 

__attribute__((used)) static const char *translate_esas2r_event_level_to_kernel(const long level)
{
	switch (level) {
	case ESAS2R_LOG_CRIT:
		return KERN_CRIT;

	case ESAS2R_LOG_WARN:
		return KERN_WARNING;

	case ESAS2R_LOG_INFO:
		return KERN_INFO;

	case ESAS2R_LOG_DEBG:
	case ESAS2R_LOG_TRCE:
	default:
		return KERN_DEBUG;
	}
}