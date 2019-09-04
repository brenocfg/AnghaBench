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
struct urfile {int /*<<< orphan*/  urd; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,struct urfile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct urfile*) ; 

__attribute__((used)) static void urfile_free(struct urfile *urf)
{
	TRACE("urfile_free: urf=%p urd=%p\n", urf, urf->urd);
	kfree(urf);
}