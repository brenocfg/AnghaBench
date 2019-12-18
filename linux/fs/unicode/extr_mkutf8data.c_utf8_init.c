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
 int /*<<< orphan*/ * corrections ; 
 int corrections_count ; 
 int /*<<< orphan*/ * unicode_data ; 
 int /*<<< orphan*/  utf8_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void utf8_init(void)
{
	unsigned int unichar;
	int i;

	for (unichar = 0; unichar != 0x110000; unichar++)
		utf8_create(&unicode_data[unichar]);

	for (i = 0; i != corrections_count; i++)
		utf8_create(&corrections[i]);
}