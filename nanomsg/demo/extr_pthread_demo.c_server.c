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
typedef  int /*<<< orphan*/  tids ;
typedef  int /*<<< orphan*/ * pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_SP_RAW ; 
 int MAXWORKERS ; 
 int /*<<< orphan*/  NN_REP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nn_bind (int,char const*) ; 
 int /*<<< orphan*/  nn_close (int) ; 
 int /*<<< orphan*/  nn_errno () ; 
 int nn_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* nn_strerror (int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  worker ; 

int server(const char *url)
{
    int fd; 
    int i;
    pthread_t tids [MAXWORKERS];
    int rc;

    /*  Create the socket. */
    fd = nn_socket(AF_SP_RAW, NN_REP);
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

    memset (tids, 0, sizeof (tids));

    /*  Start up the threads. */
    for (i = 0; i < MAXWORKERS; i++) {
        rc = pthread_create (&tids[i], NULL, worker, (void *)(intptr_t)fd);
        if (rc < 0) {
            fprintf (stderr, "pthread_create: %s\n", strerror (rc));
            nn_close (fd);
            break;
        }
    }

    /*  Now wait on them to finish. */
    for (i = 0; i < MAXWORKERS; i++) {
        if (tids[i] != NULL) {
            pthread_join (tids[i], NULL);
        }
    }
    return (-1);
}