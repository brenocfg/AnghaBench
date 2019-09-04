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
struct trace_seq {int dummy; } ;

/* Variables and functions */
 unsigned long PT_WRITABLE_MASK ; 

__attribute__((used)) static unsigned long long
process_is_writable_pte(struct trace_seq *s, unsigned long long *args)
{
	unsigned long pte = args[0];
	return pte & PT_WRITABLE_MASK;
}