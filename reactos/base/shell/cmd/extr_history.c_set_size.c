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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {int /*<<< orphan*/  prev; } ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ Bottom ; 
 TYPE_1__* Top ; 
 int /*<<< orphan*/  del (int /*<<< orphan*/ ) ; 
 scalar_t__ max_size ; 
 scalar_t__ size ; 

VOID set_size(INT new_size)
{
    ASSERT(Top && Bottom);

    while (new_size<size)
        del(Top->prev);

    max_size=new_size;
}