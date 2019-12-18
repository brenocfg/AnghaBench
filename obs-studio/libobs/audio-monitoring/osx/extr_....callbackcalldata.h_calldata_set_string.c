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
 int /*<<< orphan*/  calldata_set_data (int /*<<< orphan*/ *,char const*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static inline void calldata_set_string(calldata_t *data, const char *name,
				       const char *str)
{
	if (str)
		calldata_set_data(data, name, str, strlen(str) + 1);
	else
		calldata_set_data(data, name, NULL, 0);
}