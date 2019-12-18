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
struct fpm_child_s {int scoreboard_i; } ;

/* Variables and functions */
 struct fpm_child_s* malloc (int) ; 
 int /*<<< orphan*/  memset (struct fpm_child_s*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct fpm_child_s *fpm_child_alloc() /* {{{ */
{
	struct fpm_child_s *ret;

	ret = malloc(sizeof(struct fpm_child_s));

	if (!ret) {
		return 0;
	}

	memset(ret, 0, sizeof(*ret));
	ret->scoreboard_i = -1;
	return ret;
}