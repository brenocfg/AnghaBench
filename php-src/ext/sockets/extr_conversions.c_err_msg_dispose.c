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
struct err_s {int /*<<< orphan*/ * msg; scalar_t__ should_free; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void err_msg_dispose(struct err_s *err)
{
	if (err->msg != NULL) {
		php_error_docref(NULL, err->level, "%s", err->msg);
		if (err->should_free) {
			efree(err->msg);
		}
	}
}