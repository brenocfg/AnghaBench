#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
struct linger {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ling ;
typedef  int /*<<< orphan*/  flags ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_2__ {int /*<<< orphan*/  backlog; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  SO_LINGER ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  conn_listening ; 
 int /*<<< orphan*/  conn_new (int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listen_conn ; 
 int /*<<< orphan*/  local_transport ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  main_base ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int new_socket_unix () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 TYPE_1__ settings ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 
 int umask (int) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

__attribute__((used)) static int server_socket_unix(const char *path, int access_mask) {
    int sfd;
    struct linger ling = {0, 0};
    struct sockaddr_un addr;
    struct stat tstat;
    int flags =1;
    int old_umask;

    if (!path) {
        return 1;
    }

    if ((sfd = new_socket_unix()) == -1) {
        return 1;
    }

    /*
     * Clean up a previous socket file if we left it around
     */
    if (lstat(path, &tstat) == 0) {
        if (S_ISSOCK(tstat.st_mode))
            unlink(path);
    }

    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (void *)&flags, sizeof(flags));
    setsockopt(sfd, SOL_SOCKET, SO_KEEPALIVE, (void *)&flags, sizeof(flags));
    setsockopt(sfd, SOL_SOCKET, SO_LINGER, (void *)&ling, sizeof(ling));

    /*
     * the memset call clears nonstandard fields in some implementations
     * that otherwise mess things up.
     */
    memset(&addr, 0, sizeof(addr));

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
    assert(strcmp(addr.sun_path, path) == 0);
    old_umask = umask( ~(access_mask&0777));
    if (bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind()");
        close(sfd);
        umask(old_umask);
        return 1;
    }
    umask(old_umask);
    if (listen(sfd, settings.backlog) == -1) {
        perror("listen()");
        close(sfd);
        return 1;
    }
    if (!(listen_conn = conn_new(sfd, conn_listening,
                                 EV_READ | EV_PERSIST, 1,
                                 local_transport, main_base, NULL))) {
        fprintf(stderr, "failed to create listening connection\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}