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
typedef  int /*<<< orphan*/  ltree ;

/* Variables and functions */
 int /*<<< orphan*/  VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ltree *
copy_ltree(ltree *src)
{
	ltree	   *dst = (ltree *) palloc0(VARSIZE(src));

	memcpy(dst, src, VARSIZE(src));
	return dst;
}