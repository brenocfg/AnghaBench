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
 int ARRAY_SIZE (unsigned int*) ; 
 char const** arizona_sample_rate_text ; 
 unsigned int* arizona_sample_rate_val ; 

const char *arizona_sample_rate_val_to_name(unsigned int rate_val)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(arizona_sample_rate_val); ++i) {
		if (arizona_sample_rate_val[i] == rate_val)
			return arizona_sample_rate_text[i];
	}

	return "Illegal";
}