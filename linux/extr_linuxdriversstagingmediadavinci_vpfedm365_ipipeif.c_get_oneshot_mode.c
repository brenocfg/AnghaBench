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
typedef  enum ipipeif_input_entity { ____Placeholder_ipipeif_input_entity } ipipeif_input_entity ;

/* Variables and functions */
 int EINVAL ; 
 int IPIPEIF_INPUT_ISIF ; 
 int IPIPEIF_INPUT_MEMORY ; 
 int IPIPEIF_MODE_CONTINUOUS ; 
 int IPIPEIF_MODE_ONE_SHOT ; 

__attribute__((used)) static int get_oneshot_mode(enum ipipeif_input_entity input)
{
	if (input == IPIPEIF_INPUT_MEMORY)
		return IPIPEIF_MODE_ONE_SHOT;
	if (input == IPIPEIF_INPUT_ISIF)
		return IPIPEIF_MODE_CONTINUOUS;

	return -EINVAL;
}