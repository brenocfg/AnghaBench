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
struct section {int dummy; } ;
struct rela {int dummy; } ;

/* Variables and functions */
 struct rela* find_rela_by_dest_range (struct section*,unsigned long,int) ; 

struct rela *find_rela_by_dest(struct section *sec, unsigned long offset)
{
	return find_rela_by_dest_range(sec, offset, 1);
}