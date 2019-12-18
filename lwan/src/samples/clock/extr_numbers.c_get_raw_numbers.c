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
struct raw_number {int dummy; } ;

/* Variables and functions */
 struct raw_number const* numbers_E ; 

const struct raw_number *get_raw_numbers(void) { return numbers_E; }