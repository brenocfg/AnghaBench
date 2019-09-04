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
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __address_space_init_once (struct address_space*) ; 
 int /*<<< orphan*/  memset (struct address_space*,int /*<<< orphan*/ ,int) ; 

void address_space_init_once(struct address_space *mapping)
{
	memset(mapping, 0, sizeof(*mapping));
	__address_space_init_once(mapping);
}