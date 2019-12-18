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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  calldata_t ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_set_data (int /*<<< orphan*/ *,char const*,double*,int) ; 

__attribute__((used)) static inline void calldata_set_float(calldata_t *data, const char *name,
				      double val)
{
	calldata_set_data(data, name, &val, sizeof(val));
}