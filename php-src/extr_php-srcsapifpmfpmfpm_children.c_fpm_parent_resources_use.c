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
struct fpm_child_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpm_child_link (struct fpm_child_s*) ; 
 int /*<<< orphan*/  fpm_stdio_parent_use_pipes (struct fpm_child_s*) ; 

__attribute__((used)) static void fpm_parent_resources_use(struct fpm_child_s *child) /* {{{ */
{
	fpm_stdio_parent_use_pipes(child);
	fpm_child_link(child);
}