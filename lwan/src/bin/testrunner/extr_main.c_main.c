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
struct lwan {int dummy; } ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  lwan_init (struct lwan*) ; 
 int /*<<< orphan*/  lwan_main_loop (struct lwan*) ; 
 int /*<<< orphan*/  lwan_shutdown (struct lwan*) ; 

int
main()
{
    struct lwan l;

    lwan_init(&l);
    lwan_main_loop(&l);
    lwan_shutdown(&l);

    return EXIT_SUCCESS;
}