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
 int /*<<< orphan*/  printf (char*) ; 

int main(int argc, char *argv[])
{
#if defined (__DJGPP__)
    printf("dos\n");
#elif defined (__WIN32__)
    printf("win32\n");
#else
    printf("linux\n");
#endif // defined __DJGPP__

    return 0;
}