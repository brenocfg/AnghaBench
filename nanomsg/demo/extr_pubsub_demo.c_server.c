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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  subs ;
typedef  int /*<<< orphan*/  secs ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  NN_PUB ; 
 int /*<<< orphan*/  NN_STAT_CURRENT_CONNECTIONS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ htonl (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 scalar_t__ nn_bind (int,char const*) ; 
 int /*<<< orphan*/  nn_close (int) ; 
 int /*<<< orphan*/  nn_errno () ; 
 scalar_t__ nn_get_statistic (int,int /*<<< orphan*/ ) ; 
 int nn_send (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int nn_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* nn_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int server(const char *url)
{
    int fd; 

    /*  Create the socket. */
    fd = nn_socket (AF_SP, NN_PUB);
    if (fd < 0) {
        fprintf (stderr, "nn_socket: %s\n", nn_strerror (nn_errno ()));
        return (-1);
    }

    /*  Bind to the URL.  This will bind to the address and listen
        synchronously; new clients will be accepted asynchronously
        without further action from the calling program. */

    if (nn_bind (fd, url) < 0) {
        fprintf (stderr, "nn_bind: %s\n", nn_strerror (nn_errno ()));
        nn_close (fd);
        return (-1);
    }

    /*  Now we can just publish results.  Note that there is no explicit
        accept required.  We just start writing the information. */

    for (;;) {
        uint8_t msg[2 * sizeof (uint32_t)];
        uint32_t secs, subs;
        int rc;

        secs = (uint32_t) time (NULL);
        subs = (uint32_t) nn_get_statistic (fd, NN_STAT_CURRENT_CONNECTIONS);

        secs = htonl (secs);
        subs = htonl (subs);

        memcpy (msg, &secs, sizeof (secs));
        memcpy (msg + sizeof (secs), &subs, sizeof (subs));

        rc = nn_send (fd, msg, sizeof (msg), 0);
        if (rc < 0) {
            /*  There are several legitimate reasons this can fail.
                We note them for debugging purposes, but then ignore
                otherwise. */
            fprintf (stderr, "nn_send: %s (ignoring)\n",
                nn_strerror (nn_errno ()));
        }
        sleep(10);
    }

    /* NOTREACHED */
    nn_close (fd);
    return (-1);
}