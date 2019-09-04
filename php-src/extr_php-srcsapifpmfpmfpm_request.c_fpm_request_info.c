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
struct timeval {int dummy; } ;
struct fpm_scoreboard_proc_s {size_t content_length; int /*<<< orphan*/  script_filename; int /*<<< orphan*/  auth_user; int /*<<< orphan*/  query_string; int /*<<< orphan*/  request_method; int /*<<< orphan*/  request_uri; struct timeval tv; int /*<<< orphan*/  request_stage; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPM_REQUEST_INFO ; 
 int /*<<< orphan*/  ZLOG_WARNING ; 
 int /*<<< orphan*/  fpm_clock_get (struct timeval*) ; 
 char* fpm_php_auth_user () ; 
 size_t fpm_php_content_length () ; 
 char* fpm_php_query_string () ; 
 char* fpm_php_request_method () ; 
 char* fpm_php_request_uri () ; 
 char* fpm_php_script_filename () ; 
 struct fpm_scoreboard_proc_s* fpm_scoreboard_proc_acquire (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_scoreboard_proc_release (struct fpm_scoreboard_proc_s*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

void fpm_request_info() /* {{{ */
{
	struct fpm_scoreboard_proc_s *proc;
	char *request_uri = fpm_php_request_uri();
	char *request_method = fpm_php_request_method();
	char *script_filename = fpm_php_script_filename();
	char *query_string = fpm_php_query_string();
	char *auth_user = fpm_php_auth_user();
	size_t content_length = fpm_php_content_length();
	struct timeval now;

	fpm_clock_get(&now);

	proc = fpm_scoreboard_proc_acquire(NULL, -1, 0);
	if (proc == NULL) {
		zlog(ZLOG_WARNING, "failed to acquire proc scoreboard");
		return;
	}

	proc->request_stage = FPM_REQUEST_INFO;
	proc->tv = now;

	if (request_uri) {
		strlcpy(proc->request_uri, request_uri, sizeof(proc->request_uri));
	}

	if (request_method) {
		strlcpy(proc->request_method, request_method, sizeof(proc->request_method));
	}

	if (query_string) {
		strlcpy(proc->query_string, query_string, sizeof(proc->query_string));
	}

	if (auth_user) {
		strlcpy(proc->auth_user, auth_user, sizeof(proc->auth_user));
	}

	proc->content_length = content_length;

	/* if cgi.fix_pathinfo is set to "1" and script cannot be found (404)
		the sapi_globals.request_info.path_translated is set to NULL */
	if (script_filename) {
		strlcpy(proc->script_filename, script_filename, sizeof(proc->script_filename));
	}

	fpm_scoreboard_proc_release(proc);
}