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
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  D_LISTENER ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int chmod (char const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_enlarge_in (int) ; 
 int /*<<< orphan*/  sock_setnonblock (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 
 int unlink (char const*) ; 

int create_listen_socket_unix(const char *path, int listen_backlog) {
    int sock;

    debug(D_LISTENER, "LISTENER: UNIX creating new listening socket on path '%s'", path);

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock < 0) {
        error("LISTENER: UNIX socket() on path '%s' failed.", path);
        return -1;
    }

    sock_setnonblock(sock);
    sock_enlarge_in(sock);

    struct sockaddr_un name;
    memset(&name, 0, sizeof(struct sockaddr_un));
    name.sun_family = AF_UNIX;
    strncpy(name.sun_path, path, sizeof(name.sun_path)-1);

    errno = 0;
    if (unlink(path) == -1 && errno != ENOENT)
        error("LISTENER: failed to remove existing (probably obsolete or left-over) file on UNIX socket path '%s'.", path);

    if(bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0) {
        close(sock);
        error("LISTENER: UNIX bind() on path '%s' failed.", path);
        return -1;
    }

    // we have to chmod this to 0777 so that the client will be able
    // to read from and write to this socket.
    if(chmod(path, 0777) == -1)
        error("LISTENER: failed to chmod() socket file '%s'.", path);

    if(listen(sock, listen_backlog) < 0) {
        close(sock);
        error("LISTENER: UNIX listen() on path '%s' failed.", path);
        return -1;
    }

    debug(D_LISTENER, "LISTENER: Listening on UNIX path '%s'", path);
    return sock;
}