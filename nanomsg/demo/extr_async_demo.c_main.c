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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int client (char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int server (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

int main (int argc, char **argv)
{
    int rc;
    if (argc < 3) {
        fprintf (stderr, "Usage: %s <url> [-s|name]\n", argv[0]);
        exit (EXIT_FAILURE);
    }
    if (strcmp (argv[2], "-s") == 0) {
        rc = server (argv[1]);
    } else {
        rc = client (argv[1], argv[2]);
    }
    exit (rc == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}