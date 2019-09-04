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
 int OUTPUT_TYPE_SYNTH ; 
#define  PERF_TYPE_SYNTH 128 

__attribute__((used)) static inline int output_type(unsigned int type)
{
	switch (type) {
	case PERF_TYPE_SYNTH:
		return OUTPUT_TYPE_SYNTH;
	default:
		return type;
	}
}