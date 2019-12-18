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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
get_some_time()
{
# ifdef HAVE_GETTIMEOFDAY
    struct timeval tv;

    /* Using usec makes it less predictable. */
    gettimeofday(&tv, NULL);
    return (unsigned int)(tv.tv_sec + tv.tv_usec);
# else
    return (unsigned int)time(NULL);
# endif
}