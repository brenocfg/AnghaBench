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
struct cut_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct cut_info*) ; 

__attribute__((used)) static void cut_destroy(void *data)
{
	struct cut_info *cut = data;
	bfree(cut);
}