#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  enum libbpf_print_level { ____Placeholder_libbpf_print_level } libbpf_print_level ;
struct TYPE_2__ {int /*<<< orphan*/  very_verbose; } ;

/* Variables and functions */
 int LIBBPF_DEBUG ; 
 TYPE_1__ env ; 
 int /*<<< orphan*/  vprintf (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libbpf_print_fn(enum libbpf_print_level level,
			   const char *format, va_list args)
{
	if (!env.very_verbose && level == LIBBPF_DEBUG)
		return 0;
	vprintf(format, args);
	return 0;
}