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
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ JSSTR_HEAP ; 
 scalar_t__ jsstr_tag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline BOOL jsstr_is_heap(jsstr_t *str)
{
    return jsstr_tag(str) == JSSTR_HEAP;
}