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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  msec ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP ; 
 int /*<<< orphan*/  NN_REQ ; 
 unsigned int atoi (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 unsigned int htonl (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned int*,int) ; 
 scalar_t__ milliseconds () ; 
 int /*<<< orphan*/  nn_close (int) ; 
 scalar_t__ nn_connect (int,char const*) ; 
 int /*<<< orphan*/  nn_errno () ; 
 int nn_recv (int,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_send (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int nn_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* nn_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 

int client (const char *url, const char *msecstr)
{
    int fd;
    int rc;
    char *greeting;
    uint8_t msg[sizeof (uint32_t)];
    uint64_t start;
    uint64_t end;
    unsigned msec;

    msec = atoi(msecstr);

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

    msec = htonl(msec);
    memcpy (msg, &msec, sizeof (msec));

    start = milliseconds ();

    if (nn_send (fd, msg, sizeof (msg), 0) < 0) {
        fprintf (stderr, "nn_send: %s\n", nn_strerror (nn_errno ()));
        nn_close (fd);
        return (-1);
    }

    rc = nn_recv (fd, &msg, sizeof (msg), 0);
    if (rc < 0) {
        fprintf (stderr, "nn_recv: %s\n", nn_strerror (nn_errno ()));
        nn_close (fd);
        return (-1);
    }

    nn_close (fd);

    end = milliseconds ();

    printf ("Request took %u milliseconds.\n", (uint32_t)(end - start));
    return (0);
}