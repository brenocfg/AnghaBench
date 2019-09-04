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
struct source_location {int /*<<< orphan*/  reported; } ;

/* Variables and functions */
 int /*<<< orphan*/  REPORTED_BIT ; 
 int test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool was_reported(struct source_location *location)
{
	return test_and_set_bit(REPORTED_BIT, &location->reported);
}