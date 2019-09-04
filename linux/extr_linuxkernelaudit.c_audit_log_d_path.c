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
struct path {int dummy; } ;
struct audit_buffer {int /*<<< orphan*/  gfp_mask; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 scalar_t__ PATH_MAX ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,char const*) ; 
 int /*<<< orphan*/  audit_log_string (struct audit_buffer*,char*) ; 
 int /*<<< orphan*/  audit_log_untrustedstring (struct audit_buffer*,char*) ; 
 char* d_path (struct path const*,char*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 

void audit_log_d_path(struct audit_buffer *ab, const char *prefix,
		      const struct path *path)
{
	char *p, *pathname;

	if (prefix)
		audit_log_format(ab, "%s", prefix);

	/* We will allow 11 spaces for ' (deleted)' to be appended */
	pathname = kmalloc(PATH_MAX+11, ab->gfp_mask);
	if (!pathname) {
		audit_log_string(ab, "<no_memory>");
		return;
	}
	p = d_path(path, pathname, PATH_MAX+11);
	if (IS_ERR(p)) { /* Should never happen since we send PATH_MAX */
		/* FIXME: can we save some information here? */
		audit_log_string(ab, "<too_long>");
	} else
		audit_log_untrustedstring(ab, p);
	kfree(pathname);
}