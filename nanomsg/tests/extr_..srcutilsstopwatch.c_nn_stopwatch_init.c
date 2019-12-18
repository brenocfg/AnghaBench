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
typedef  int uint64_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct nn_stopwatch {int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

void nn_stopwatch_init (struct nn_stopwatch *self)
{
    int rc;
    struct timeval tv;

    rc = gettimeofday (&tv, NULL);
    assert (rc == 0);
    self->start = (uint64_t) (((uint64_t) tv.tv_sec) * 1000000 + tv.tv_usec);
}