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
struct virtual_output {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,unsigned int const,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int const,char const*) ; 

__attribute__((used)) static inline void
virtual_output_print(const struct virtual_output *vo, const unsigned int flags, const char *str)
{
    (*vo->func)(vo->arg, flags, str);
}