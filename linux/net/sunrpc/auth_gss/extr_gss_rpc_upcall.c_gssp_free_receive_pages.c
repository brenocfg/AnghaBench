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
struct gssx_arg_accept_sec_context {int npages; scalar_t__* pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 

__attribute__((used)) static void gssp_free_receive_pages(struct gssx_arg_accept_sec_context *arg)
{
	int i;

	for (i = 0; i < arg->npages && arg->pages[i]; i++)
		__free_page(arg->pages[i]);

	kfree(arg->pages);
}