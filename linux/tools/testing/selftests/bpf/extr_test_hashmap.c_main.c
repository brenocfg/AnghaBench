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
 scalar_t__ test_hashmap_empty () ; 
 scalar_t__ test_hashmap_generic () ; 
 scalar_t__ test_hashmap_multimap () ; 

int main(int argc, char **argv)
{
	bool failed = false;

	if (test_hashmap_generic())
		failed = true;
	if (test_hashmap_multimap())
		failed = true;
	if (test_hashmap_empty())
		failed = true;

	return failed;
}