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

/* Variables and functions */
 scalar_t__ ALIGN (uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_ALIGN ; 

__attribute__((used)) static inline void *rx_agg_align(void *data)
{
	return (void *)ALIGN((uintptr_t)data, RX_ALIGN);
}