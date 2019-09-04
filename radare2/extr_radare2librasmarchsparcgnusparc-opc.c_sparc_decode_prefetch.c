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
 char const* lookup_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prefetch_table ; 

const char *
sparc_decode_prefetch (int value)
{
  return lookup_value (prefetch_table, value);
}