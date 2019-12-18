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
struct block_info {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 struct block_info* zalloc (int) ; 

struct block_info *block_info__new(void)
{
	struct block_info *bi = zalloc(sizeof(*bi));

	if (bi)
		refcount_set(&bi->refcnt, 1);
	return bi;
}