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
#define  OUTPUT_TYPE_SYNTH 128 
 unsigned int PERF_TYPE_SYNTH ; 

__attribute__((used)) static inline unsigned int attr_type(unsigned int type)
{
	switch (type) {
	case OUTPUT_TYPE_SYNTH:
		return PERF_TYPE_SYNTH;
	default:
		return type;
	}
}