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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* imagefile ; 
 int quiet ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
indicate_writing(const char *mtd)
{
	if (quiet < 2)
		fprintf(stderr, "\nWriting from %s to %s ... ", imagefile, mtd);

	if (!quiet)
		fprintf(stderr, " [ ]");
}