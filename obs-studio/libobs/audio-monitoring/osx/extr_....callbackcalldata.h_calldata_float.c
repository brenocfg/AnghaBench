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
 int /*<<< orphan*/  calldata_get_float (int /*<<< orphan*/  const*,char const*,double*) ; 

__attribute__((used)) static inline double calldata_float(const calldata_t *data, const char *name)
{
	double val = 0.0;
	calldata_get_float(data, name, &val);
	return val;
}