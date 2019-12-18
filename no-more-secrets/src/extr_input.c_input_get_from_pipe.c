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
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  error_log (char*) ; 
 int input_get (unsigned char**,int /*<<< orphan*/ *) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 

int input_get_from_pipe(unsigned char** dest)
{
	int r;

	if (isatty(STDIN_FILENO))
	{
		error_log("Input data from a piped or redirected source is required.");
		return -1;
	}

	r = input_get(dest, NULL);
	if (r < 0)
	{
		error_log("Could not get input.");
		return -1;
	}
	if (r == 0)
	{
		error_log("No input provided.");
		return -1;
	}

	return r;
}