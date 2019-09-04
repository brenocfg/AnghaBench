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
typedef  int /*<<< orphan*/  sock_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int chdir (char const*) ; 
 int /*<<< orphan*/  closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execle (char const*,char const*,char const*,...) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  send (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int mg_start_process(const char *interp, const char *cmd,
                            const char *env, const char *envp[],
                            const char *dir, sock_t sock) {
  char buf[500];
  pid_t pid = fork();
  (void) env;

  if (pid == 0) {
    /*
     * In Linux `chdir` declared with `warn_unused_result` attribute
     * To shutup compiler we have yo use result in some way
     */
    int tmp = chdir(dir);
    (void) tmp;
    (void) dup2(sock, 0);
    (void) dup2(sock, 1);
    closesocket(sock);

    /*
     * After exec, all signal handlers are restored to their default values,
     * with one exception of SIGCHLD. According to POSIX.1-2001 and Linux's
     * implementation, SIGCHLD's handler will leave unchanged after exec
     * if it was set to be ignored. Restore it to default action.
     */
    signal(SIGCHLD, SIG_DFL);

    if (interp == NULL) {
      execle(cmd, cmd, (char *) 0, envp); /* (char *) 0 to squash warning */
    } else {
      execle(interp, interp, cmd, (char *) 0, envp);
    }
    snprintf(buf, sizeof(buf),
             "Status: 500\r\n\r\n"
             "500 Server Error: %s%s%s: %s",
             interp == NULL ? "" : interp, interp == NULL ? "" : " ", cmd,
             strerror(errno));
    send(1, buf, strlen(buf), 0);
    _exit(EXIT_FAILURE); /* exec call failed */
  }

  return (pid != 0);
}