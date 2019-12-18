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
typedef  int /*<<< orphan*/  uint16_t ;
struct trace_seq {int dummy; } ;

/* Variables and functions */
 scalar_t__ le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long long
process___le16_to_cpup(struct trace_seq *s, unsigned long long *args)
{
	uint16_t *val = (uint16_t *) (unsigned long) args[0];
	return val ? (long long) le16toh(*val) : 0;
}