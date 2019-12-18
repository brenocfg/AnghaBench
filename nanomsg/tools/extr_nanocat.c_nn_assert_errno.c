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
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* nn_strerror (int) ; 
 int /*<<< orphan*/  stderr ; 

void nn_assert_errno (int flag, char *description)
{
    int err;

    if (!flag) {
        err = errno;
        fprintf (stderr, "%s: %s\n", description, nn_strerror (err));
        exit (3);
    }
}