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
struct TYPE_2__ {int /*<<< orphan*/  constructor; } ;
typedef  int /*<<< orphan*/  MainClass ;

/* Variables and functions */
 TYPE_1__* G_OBJECT_CLASS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_type_class_peek_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_constructor ; 
 int /*<<< orphan*/  main_parent_class ; 

__attribute__((used)) static void main_class_init (MainClass * klass) {
	main_parent_class = g_type_class_peek_parent (klass);
	G_OBJECT_CLASS (klass)->constructor = main_constructor;
}