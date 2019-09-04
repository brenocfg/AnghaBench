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
struct table_header {int dummy; } ;

/* Variables and functions */
 size_t ALIGN (int,int) ; 

__attribute__((used)) static inline size_t table_size(size_t len, size_t el_size)
{
	return ALIGN(sizeof(struct table_header) + len * el_size, 8);
}