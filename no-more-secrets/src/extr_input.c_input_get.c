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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FIONREAD ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error_log (char*,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  stdout ; 

int input_get(unsigned char** dest, char *prompt)
{
	int r, input_len;
	fd_set input_stream;
	struct timeval timeout;
	void *timeout_p;

	FD_ZERO(&input_stream);
	input_len = 0;

	timeout.tv_sec  = 10;
	timeout.tv_usec = 0;

	if (isatty(STDIN_FILENO))
	{
		timeout_p = NULL;
		if (prompt != NULL)
		{
			printf("%s", prompt);
			fflush(stdout);
		}
	}
	else
	{
		timeout_p = &timeout;
	}

	FD_SET(STDIN_FILENO, &input_stream);
	r = select(FD_SETSIZE, &input_stream, NULL, NULL, timeout_p);
	if (r < 0)
	{
		error_log("Error while waiting for input data. Errno: %i", errno);
		return -1;
	}
	if (r > 0)
	{
		r = ioctl(STDIN_FILENO, FIONREAD, &input_len);
		if (r < 0)
		{
			error_log("Could not determine length of input. Errno: %i", errno);
			return -1;
		}
		if (input_len > 0)
		{
			*dest = malloc(input_len);
			if (*dest == NULL)
			{
				error_log("Memory allocation error.");
				return -1;
			}
			r = read(STDIN_FILENO, *dest, input_len);
			if (r < 0)
			{
				error_log("Input read error. Errno: %i", errno);
				return -1;
			}
		}
	}

	FD_CLR(STDIN_FILENO, &input_stream);

	return input_len;
}