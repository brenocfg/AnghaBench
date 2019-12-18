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
struct thunk {unsigned int index; int /*<<< orphan*/  call_stubless; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_stubless_func ; 
 struct thunk thunk_template ; 

__attribute__((used)) static inline void init_thunk( struct thunk *thunk, unsigned int index )
{
    *thunk = thunk_template;
    thunk->index = index;
    thunk->call_stubless = call_stubless_func;
}