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
typedef  enum event_type { ____Placeholder_event_type } event_type ;

/* Variables and functions */
 int __read_expected (int,char const*,int) ; 

__attribute__((used)) static int read_expected(enum event_type expect, const char *str)
{
	return __read_expected(expect, str, 1);
}