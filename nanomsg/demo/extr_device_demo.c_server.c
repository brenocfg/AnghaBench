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
typedef  int /*<<< orphan*/  username ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_hour; } ;
typedef  int /*<<< orphan*/  greeting ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  NN_REP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ getpid () ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_close (int) ; 
 scalar_t__ nn_connect (int,char const*) ; 
 int /*<<< orphan*/  nn_errno () ; 
 int nn_recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int nn_send (int,char*,int,int /*<<< orphan*/ ) ; 
 int nn_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* nn_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int server(const char *url)
{
    int fd; 

    /*  Create the socket. */
    fd = nn_socket (AF_SP, NN_REP);
    if (fd < 0) {
        fprintf (stderr, "nn_socket: %s\n", nn_strerror (nn_errno ()));
        return (-1);
    }

    /*  Connect to the URL.  This will connect to the address and listen
        synchronously; new clients will be accepted asynchronously
        without further action from the calling program. */

    if (nn_connect (fd, url) < 0) {
        fprintf (stderr, "nn_connect: %s\n", nn_strerror (nn_errno ()));
        nn_close (fd);
        return (-1);
    }

    /*  Now we can just process results.  Note that there is no explicit
        accept required.  We just receive a request, and reply to it.
        Its important to note that we must not issue two receives in a
        row without replying first, or the following receive(s) will
        cancel any unreplied requests. */

    for (;;) {
        char username[128];
        char greeting[128];
        time_t secs;
        struct tm *now;
        char *daytime;
        int rc;
        char *fmt;

        rc = nn_recv (fd, username, sizeof (username), 0);
        if (rc < 0) {
            /*  Any error here is unexpected. */
            fprintf (stderr, "nn_recv: %s\n", nn_strerror (nn_errno ()));
            break;
        }

        secs = time (NULL);
        now = localtime (&secs);
        if (now->tm_hour < 12) {
            daytime = "morning";

        } else if (now->tm_hour < 17) {
            daytime = "afternoon";

        } else if (now->tm_hour < 20) {
            daytime = "evening";

        } else {
            daytime = "night";
        }

        /*  Ensure ASCIIZ terminated string. */
        if (rc < sizeof (username)) {
            username[rc] = '\0';
        } else {
            username[sizeof (username) - 1] = '\0';
        }

        fmt = "Good %s, %s (from %d).";

        /*  Technically this might be overly pessimistic about size. */
        if ((strlen (username) + strlen (daytime) + strlen (fmt)) >=
            sizeof (greeting)) {

            fmt = "I'm sorry, your name is too long.  But good %s anyway.";
        }

        /*  snprintf would be safer, but the above check protects us. */
        sprintf (greeting, fmt, daytime, username, (int)getpid());

        rc = nn_send (fd, greeting, strlen (greeting), 0);
        if (rc < 0) {
            /*  There are several legitimate reasons this can fail.
                We note them for debugging purposes, but then ignore
                otherwise.  If the socket is closed or failing, we will
                notice in recv above, and exit then. */
            fprintf (stderr, "nn_send: %s (ignoring)\n",
                nn_strerror (nn_errno ()));
        }
    }

    nn_close (fd);
    return (-1);
}