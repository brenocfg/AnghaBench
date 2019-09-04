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
struct sti_struct {int dummy; } ;

/* Variables and functions */
 struct sti_struct* default_sti ; 
 int /*<<< orphan*/  default_sti_path ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sticore_check_for_default_sti(struct sti_struct *sti, char *path)
{
	if (strcmp (path, default_sti_path) == 0)
		default_sti = sti;
}