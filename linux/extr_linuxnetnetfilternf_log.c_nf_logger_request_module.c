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
typedef  enum nf_log_type { ____Placeholder_nf_log_type } nf_log_type ;

/* Variables and functions */
 int /*<<< orphan*/ *** loggers ; 
 int /*<<< orphan*/  request_module (char*,int,int) ; 

void nf_logger_request_module(int pf, enum nf_log_type type)
{
	if (loggers[pf][type] == NULL)
		request_module("nf-logger-%u-%u", pf, type);
}