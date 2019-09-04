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
struct buffer_page {int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 unsigned long RB_WRITE_MASK ; 
 unsigned long local_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned long rb_page_entries(struct buffer_page *bpage)
{
	return local_read(&bpage->entries) & RB_WRITE_MASK;
}