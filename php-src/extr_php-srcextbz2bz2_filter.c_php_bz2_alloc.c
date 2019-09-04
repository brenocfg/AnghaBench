#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  persistent; } ;
typedef  TYPE_1__ php_bz2_filter_data ;

/* Variables and functions */
 scalar_t__ safe_pemalloc (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *php_bz2_alloc(void *opaque, int items, int size)
{
	return (void *)safe_pemalloc(items, size, 0, ((php_bz2_filter_data*)opaque)->persistent);
}