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
struct fpm_array_s {scalar_t__ used; } ;

/* Variables and functions */
 void* fpm_array_item (struct fpm_array_s*,scalar_t__) ; 

__attribute__((used)) static inline void *fpm_array_item_last(struct fpm_array_s *a) /* {{{ */
{
	return fpm_array_item(a, a->used - 1);
}