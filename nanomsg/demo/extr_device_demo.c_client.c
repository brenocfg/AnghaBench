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

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  NN_MSG ; 
 int /*<<< orphan*/  NN_REQ ; 
 char* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  nn_close (int) ; 
 scalar_t__ nn_connect (int,char const*) ; 
 int /*<<< orphan*/  nn_errno () ; 
 int /*<<< orphan*/  nn_freemsg (char*) ; 
 int nn_recv (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_send (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nn_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* nn_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  usleep (int) ; 

int client (const char *url, const char *username)
{
    int fd;
    int rc;
    char *greeting;
    char *msg;

    fd = nn_socket (AF_SP, NN_REQ);
    if (fd < 0) {
        fprintf (stderr, "nn_socket: %s\n", nn_strerror (nn_errno ()));
        return (-1);
    }

    if (nn_connect (fd, url) < 0) {
        fprintf (stderr, "nn_socket: %s\n", nn_strerror (nn_errno ()));
        nn_close (fd);
        return (-1);        
    }

    usleep(1000);

    if (nn_send (fd, username, strlen (username), 0) < 0) {
        fprintf (stderr, "nn_send: %s\n", nn_strerror (nn_errno ()));
        nn_close (fd);
        return (-1);
    }

    /*  Here we ask the library to allocate response buffer for us (NN_MSG). */
    rc = nn_recv (fd, &msg, NN_MSG, 0);
    if (rc < 0) {
        fprintf (stderr, "nn_recv: %s\n", nn_strerror (nn_errno ()));
        nn_close (fd);
        return (-1);
    }

    nn_close (fd);

    /*  Response is not ASCIIZ terminated. */
    greeting = calloc (rc + 1, 1);
    if (greeting == NULL) {
        fprintf (stderr, "calloc: %s\n", strerror (errno));
        return (-1);
    }
    memcpy(greeting, msg, rc);

    nn_freemsg (msg);
    printf ("%s\n", greeting); 
    free (greeting);
    return (0);
}