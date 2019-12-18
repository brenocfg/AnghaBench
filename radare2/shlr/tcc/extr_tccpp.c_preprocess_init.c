#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ifdef_stack_ptr; } ;
struct TYPE_4__ {scalar_t__* pack_stack; scalar_t__* pack_stack_ptr; int /*<<< orphan*/  ifdef_stack_ptr; int /*<<< orphan*/  ifdef_stack; int /*<<< orphan*/  include_stack; int /*<<< orphan*/  include_stack_ptr; } ;
typedef  TYPE_1__ TCCState ;

/* Variables and functions */
 TYPE_3__* file ; 
 scalar_t__ vstack ; 
 scalar_t__ vtop ; 

void preprocess_init(TCCState *s1)
{
	s1->include_stack_ptr = s1->include_stack;
	/* XXX: move that before to avoid having to initialize
	   file->ifdef_stack_ptr ? */
	s1->ifdef_stack_ptr = s1->ifdef_stack;
	file->ifdef_stack_ptr = s1->ifdef_stack_ptr;

	vtop = vstack - 1;
	s1->pack_stack[0] = 0;
	s1->pack_stack_ptr = s1->pack_stack;
}