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
struct TYPE_2__ {char* name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */

__attribute__((used)) static bool ovl_is_temp_index(struct dentry *index)
{
	return index->d_name.name[0] == '#';
}