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
 int /*<<< orphan*/  calldata_get_string (int /*<<< orphan*/  const*,char const*,char const**) ; 

__attribute__((used)) static inline const char *calldata_string(const calldata_t *data,
					  const char *name)
{
	const char *val = NULL;
	calldata_get_string(data, name, &val);
	return val;
}