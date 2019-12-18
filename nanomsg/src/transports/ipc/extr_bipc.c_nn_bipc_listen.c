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
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
struct sockaddr_storage {int /*<<< orphan*/  ss_family; } ;
struct sockaddr {int dummy; } ;
struct nn_bipc {int /*<<< orphan*/  usock; int /*<<< orphan*/  ep; } ;
typedef  int /*<<< orphan*/  ss ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 scalar_t__ ECONNREFUSED ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  NN_BIPC_BACKLOG ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_bipc_start_accepting (struct nn_bipc*) ; 
 char* nn_ep_getaddr (int /*<<< orphan*/ ) ; 
 int nn_usock_bind (int /*<<< orphan*/ *,struct sockaddr*,int) ; 
 int nn_usock_listen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nn_usock_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_usock_stop (int /*<<< orphan*/ *) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 
 int unlink (char const*) ; 

__attribute__((used)) static int nn_bipc_listen (struct nn_bipc *self)
{
    int rc;
    struct sockaddr_storage ss;
    struct sockaddr_un *un;
    const char *addr;
#if defined NN_HAVE_UNIX_SOCKETS
    int fd;
#endif

    /*  First, create the AF_UNIX address. */
    addr = nn_ep_getaddr (self->ep);
    memset (&ss, 0, sizeof (ss));
    un = (struct sockaddr_un*) &ss;
    nn_assert (strlen (addr) < sizeof (un->sun_path));
    ss.ss_family = AF_UNIX;
    strncpy (un->sun_path, addr, sizeof (un->sun_path));

    /*  Delete the IPC file left over by eventual previous runs of
        the application. We'll check whether the file is still in use by
        connecting to the endpoint. On Windows plaform, NamedPipe is used
        which does not have an underlying file. */
#if defined NN_HAVE_UNIX_SOCKETS
    fd = socket (AF_UNIX, SOCK_STREAM, 0);
    if (fd >= 0) {
        rc = fcntl (fd, F_SETFL, O_NONBLOCK);
        errno_assert (rc != -1 || errno == EINVAL);
        rc = connect (fd, (struct sockaddr*) &ss,
            sizeof (struct sockaddr_un));
        if (rc == -1 && errno == ECONNREFUSED) {
            rc = unlink (addr);
            errno_assert (rc == 0 || errno == ENOENT);
        }
        rc = close (fd);
        errno_assert (rc == 0);
    }
#endif

    /*  Start listening for incoming connections. */
    rc = nn_usock_start (&self->usock, AF_UNIX, SOCK_STREAM, 0);
    if (rc < 0) {
        return rc;
    }

    rc = nn_usock_bind (&self->usock,
        (struct sockaddr*) &ss, sizeof (struct sockaddr_un));
    if (rc < 0) {
        nn_usock_stop (&self->usock);
        return rc;
    }

    rc = nn_usock_listen (&self->usock, NN_BIPC_BACKLOG);
    if (rc < 0) {
        nn_usock_stop (&self->usock);
        return rc;
    }
    nn_bipc_start_accepting (self);

    return 0;
}