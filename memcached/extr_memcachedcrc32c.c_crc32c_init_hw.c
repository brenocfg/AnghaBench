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
 int /*<<< orphan*/  LONG ; 
 int /*<<< orphan*/  SHORT ; 
 int /*<<< orphan*/  crc32c_long ; 
 int /*<<< orphan*/  crc32c_short ; 
 int /*<<< orphan*/  crc32c_zeros (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crc32c_init_hw(void)
{
    crc32c_zeros(crc32c_long, LONG);
    crc32c_zeros(crc32c_short, SHORT);
}