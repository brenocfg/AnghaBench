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
typedef  int /*<<< orphan*/  calldata_t ;

/* Variables and functions */
 int calldata_get_data (int /*<<< orphan*/  const*,char const*,long long*,int) ; 

__attribute__((used)) static inline bool calldata_get_int(const calldata_t *data, const char *name,
				    long long *val)
{
	return calldata_get_data(data, name, val, sizeof(*val));
}