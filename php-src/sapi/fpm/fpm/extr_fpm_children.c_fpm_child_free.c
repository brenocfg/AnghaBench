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
struct fpm_child_s {struct fpm_child_s* log_stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct fpm_child_s*) ; 
 int /*<<< orphan*/  zlog_stream_close (struct fpm_child_s*) ; 

__attribute__((used)) static void fpm_child_free(struct fpm_child_s *child) /* {{{ */
{
	if (child->log_stream) {
		zlog_stream_close(child->log_stream);
		free(child->log_stream);
	}
	free(child);
}