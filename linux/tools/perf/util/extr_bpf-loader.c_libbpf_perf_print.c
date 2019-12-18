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
typedef  int /*<<< orphan*/  va_list ;
typedef  enum libbpf_print_level { ____Placeholder_libbpf_print_level } libbpf_print_level ;

/* Variables and functions */
 int /*<<< orphan*/  pr_fmt (char const*) ; 
 int veprintf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int libbpf_perf_print(enum libbpf_print_level level __attribute__((unused)),
			      const char *fmt, va_list args)
{
	return veprintf(1, verbose, pr_fmt(fmt), args);
}