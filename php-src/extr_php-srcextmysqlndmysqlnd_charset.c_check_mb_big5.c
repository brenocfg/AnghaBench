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
 scalar_t__ valid_big5head (char const) ; 
 scalar_t__ valid_big5tail (char const) ; 

__attribute__((used)) static unsigned int check_mb_big5(const char * const start, const char * const end)
{
	return (valid_big5head(*(start)) && (end - start) > 1 && valid_big5tail(*(start + 1)) ? 2 : 0);
}