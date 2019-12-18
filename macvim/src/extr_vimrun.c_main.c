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
 scalar_t__ GetCommandLine () ; 
 char* _acmdln ; 
 int /*<<< orphan*/  _getch () ; 
 scalar_t__ _kbhit () ; 
 char* _oscmd ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  puts (char const*) ; 
 int system (char const*) ; 

int
main(void)
{
    const char	*p;
    int		retval;
    int		inquote = 0;
    int		silent = 0;

#ifdef __BORLANDC__
    p = _oscmd;
#else
# if defined(__MINGW32__) || defined(__CYGWIN__)
    p = (const char *)GetCommandLine();
# else
    p = _acmdln;
# endif
#endif
    /*
     * Skip the executable name, which might be in "".
     */
    while (*p)
    {
	if (*p == '"')
	    inquote = !inquote;
	else if (!inquote && *p == ' ')
	{
	    ++p;
	    break;
	}
	++p;
    }

    /*
     * "-s" argument: don't wait for a key hit.
     */
    if (p[0] == '-' && p[1] == 's' && p[2] == ' ')
    {
	silent = 1;
	p += 3;
	while (*p == ' ')
	    ++p;
    }

    /* Print the command, including quotes and redirection. */
    puts(p);

    /*
     * Do it!
     */
    retval = system(p);

    if (retval == -1)
	perror("vimrun system(): ");
    else if (retval != 0)
	printf("shell returned %d\n", retval);

    if (!silent)
    {
	puts("Hit any key to close this window...");

#ifndef __CYGWIN__
	while (_kbhit())
	    (void)_getch();
#endif
	(void)_getch();
    }

    return retval;
}