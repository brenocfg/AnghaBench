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
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void print_payload(char *data, int len)
{
	int i;

	if (!len)
		return;

	if (len > 70)
		len = 70;

	fprintf(stderr, "payload: ");
	for (i = 0; i < len; i++)
		fprintf(stderr, "%02hhx ", data[i]);
	fprintf(stderr, "\n");
}