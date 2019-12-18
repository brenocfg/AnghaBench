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
 int LIBBPF_DEBUG ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 
 int /*<<< orphan*/  vprintf (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libbpf_debug_print(enum libbpf_print_level level,
			      const char *format, va_list args)
{
	if (level != LIBBPF_DEBUG) {
		vprintf(format, args);
		return 0;
	}

	if (!strstr(format, "verifier log"))
		return 0;
	vprintf("%s", args);
	return 0;
}