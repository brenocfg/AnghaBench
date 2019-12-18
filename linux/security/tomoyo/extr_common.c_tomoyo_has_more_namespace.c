#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ns; scalar_t__ eof; } ;
struct tomoyo_io_buffer {scalar_t__ type; TYPE_2__ r; } ;
struct TYPE_3__ {int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 scalar_t__ TOMOYO_EXCEPTIONPOLICY ; 
 scalar_t__ TOMOYO_PROFILE ; 
 int /*<<< orphan*/  tomoyo_namespace_list ; 

__attribute__((used)) static inline bool tomoyo_has_more_namespace(struct tomoyo_io_buffer *head)
{
	return (head->type == TOMOYO_EXCEPTIONPOLICY ||
		head->type == TOMOYO_PROFILE) && head->r.eof &&
		head->r.ns->next != &tomoyo_namespace_list;
}