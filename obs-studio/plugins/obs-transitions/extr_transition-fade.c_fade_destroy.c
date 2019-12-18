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
struct fade_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct fade_info*) ; 

__attribute__((used)) static void fade_destroy(void *data)
{
	struct fade_info *fade = data;
	bfree(fade);
}