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
typedef  int /*<<< orphan*/  timeout_error_t ;
struct timeouts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 struct timeouts* lwan_aligned_alloc (int,int) ; 
 struct timeouts* timeouts_init (struct timeouts*) ; 

struct timeouts *timeouts_open(timeout_error_t *error)
{
    struct timeouts *T;

    if ((T = lwan_aligned_alloc(sizeof *T, 64)))
        return timeouts_init(T);

    *error = errno;

    return NULL;
}