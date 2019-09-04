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
 int eat_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_body ; 

__attribute__((used)) static int count_instructions(void)
{
	return eat_cpu(test_body);
}