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
struct epbuf_handler {int /*<<< orphan*/ * ring; int /*<<< orphan*/ * info; scalar_t__ size; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fjes_hw_free_epbuf(struct epbuf_handler *epbh)
{
	vfree(epbh->buffer);
	epbh->buffer = NULL;
	epbh->size = 0;

	epbh->info = NULL;
	epbh->ring = NULL;
}