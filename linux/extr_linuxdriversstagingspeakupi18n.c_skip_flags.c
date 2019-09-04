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
 scalar_t__ strchr (char*,char) ; 

__attribute__((used)) static char *skip_flags(char *input)
{
	while ((*input != '\0') && strchr(" 0+-#", *input))
		input++;
	return input;
}