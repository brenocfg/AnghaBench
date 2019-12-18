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
struct marker {struct marker* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  has_data_type_information (struct marker*) ; 

__attribute__((used)) static struct marker *next_type_marker(struct marker *m)
{
	while (m && !has_data_type_information(m))
		m = m->next;
	return m;
}