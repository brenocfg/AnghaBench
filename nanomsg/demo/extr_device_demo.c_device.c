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
 int /*<<< orphan*/  AF_SP_RAW ; 
 int /*<<< orphan*/  NN_REP ; 
 int /*<<< orphan*/  NN_REQ ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 scalar_t__ nn_bind (int,char const*) ; 
 scalar_t__ nn_device (int,int) ; 
 int /*<<< orphan*/  nn_errno () ; 
 int nn_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* nn_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int device (const char *url1, const char *url2)
{
    int s1, s2, rv;
    s1 = nn_socket (AF_SP_RAW, NN_REQ);
    if (s1 < 0) {
        fprintf (stderr, "nn_socket: %s\n", nn_strerror (nn_errno ()));
        return (-1);
    }
    if (nn_bind (s1, url1) < 0) {
        fprintf (stderr, "nn_bind1(%s): %s\n", url1, nn_strerror (nn_errno ()));
        return (-1);
    }
    s2 = nn_socket (AF_SP_RAW, NN_REP);
    if (s2 < 0) {
        fprintf (stderr, "nn_socket: %s\n", nn_strerror(nn_errno ()));
        return (-1);
    }
    if (nn_bind (s2, url2) < 0) {
        fprintf (stderr, "nn_bind2(%s): %s\n", url2, nn_strerror (nn_errno ()));
        return (-1);
    }

    if (nn_device (s1, s2) != 0) {
        fprintf (stderr, "nn_device: %s\n", nn_strerror (nn_errno ()));
        return (-1);
    }
    return (0);
}