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
struct data {int len; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 struct data data_grow_for (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  empty_data ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 

struct data data_copy_mem(const char *mem, int len)
{
	struct data d;

	d = data_grow_for(empty_data, len);

	d.len = len;
	memcpy(d.val, mem, len);

	return d;
}