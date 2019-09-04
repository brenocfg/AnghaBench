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
struct callchain_param {int dummy; } ;

/* Variables and functions */
 int parse_callchain_record (char const*,struct callchain_param*) ; 

int parse_callchain_record_opt(const char *arg, struct callchain_param *param)
{
	return parse_callchain_record(arg, param);
}