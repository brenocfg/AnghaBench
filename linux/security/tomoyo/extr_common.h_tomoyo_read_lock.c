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
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomoyo_ss ; 

__attribute__((used)) static inline int tomoyo_read_lock(void)
{
	return srcu_read_lock(&tomoyo_ss);
}