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
struct argv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_init (struct argv*) ; 

struct argv
argv_new(void)
{
    struct argv ret;
    argv_init(&ret);
    return ret;
}