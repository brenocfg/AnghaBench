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
struct type_set {int /*<<< orphan*/  negset; int /*<<< orphan*/  types; } ;

/* Variables and functions */
 int /*<<< orphan*/  ebitmap_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void type_set_init(struct type_set *t)
{
	ebitmap_init(&t->types);
	ebitmap_init(&t->negset);
}