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
struct qdio_buffer_element {int eflags; } ;

/* Variables and functions */
 int SBAL_EFLAGS_LAST_ENTRY ; 

__attribute__((used)) static inline int qeth_is_last_sbale(struct qdio_buffer_element *sbale)
{
	return (sbale->eflags & SBAL_EFLAGS_LAST_ENTRY);
}