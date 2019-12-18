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
 int /*<<< orphan*/  CFAG12864B_SIZE ; 
 int /*<<< orphan*/  cfag12864b_buffer ; 
 int /*<<< orphan*/  cfag12864b_mem ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfag12864b_blit(void)
{
	memcpy(cfag12864b_mem, cfag12864b_buffer, CFAG12864B_SIZE);
}