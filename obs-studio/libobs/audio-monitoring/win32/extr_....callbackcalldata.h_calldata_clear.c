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
struct calldata {int size; scalar_t__ stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void calldata_clear(struct calldata *data)
{
	if (data->stack) {
		data->size = sizeof(size_t);
		memset(data->stack, 0, sizeof(size_t));
	}
}