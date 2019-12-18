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
struct audioformat {struct audioformat* chmap; struct audioformat* rate_table; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct audioformat*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void audioformat_free(struct audioformat *fp)
{
	list_del(&fp->list); /* unlink for avoiding double-free */
	kfree(fp->rate_table);
	kfree(fp->chmap);
	kfree(fp);
}