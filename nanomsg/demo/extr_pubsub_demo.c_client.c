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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  subs ;
typedef  int /*<<< orphan*/  secs ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  hhmmss ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  NN_SUB ; 
 int /*<<< orphan*/  NN_SUB_SUBSCRIBE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  localtime (scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nn_close (int) ; 
 scalar_t__ nn_connect (int,char const*) ; 
 int /*<<< orphan*/  nn_errno () ; 
 int nn_recv (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int nn_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* nn_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/ ) ; 

int client (const char *url)
{
    int fd;
    int rc;

    fd = nn_socket (AF_SP, NN_SUB);
    if (fd < 0) {
        fprintf (stderr, "nn_socket: %s\n", nn_strerror (nn_errno ()));
        return (-1);
    }

    if (nn_connect (fd, url) < 0) {
        fprintf (stderr, "nn_socket: %s\n", nn_strerror (nn_errno ()));
        nn_close (fd);
        return (-1);        
    }

    /*  We want all messages, so just subscribe to the empty value. */
    if (nn_setsockopt (fd, NN_SUB, NN_SUB_SUBSCRIBE, "", 0) < 0) {
        fprintf (stderr, "nn_setsockopt: %s\n", nn_strerror (nn_errno ()));
        nn_close (fd);
        return (-1);        
    }

    for (;;) {
        uint8_t msg[2 * sizeof (uint32_t)];
        char hhmmss[9];  /* HH:MM:SS\0 */
        uint32_t subs, secs;
        time_t t;

        rc = nn_recv (fd, msg, sizeof (msg), 0);
        if (rc < 0) {
            fprintf (stderr, "nn_recv: %s\n", nn_strerror (nn_errno ()));
            break;
        }
        if (rc != sizeof (msg)) {
            fprintf (stderr, "nn_recv: got %d bytes, wanted %d\n",
                rc, (int)sizeof (msg));
             break;
        }
        memcpy (&secs, msg, sizeof (secs));
        memcpy (&subs, msg + sizeof (secs), sizeof (subs));

        t = (time_t) ntohl(secs);
        strftime (hhmmss, sizeof (hhmmss), "%T", localtime (&t));

        printf ("%s <pid %u> There are %u clients connected.\n", hhmmss,
            (unsigned) getpid(), (unsigned) ntohl(subs));
    }

    nn_close (fd);
    return (-1);
}