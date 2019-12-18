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
 int /*<<< orphan*/  jsstr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ jsstr_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline BOOL jsstr_eq(jsstr_t *left, jsstr_t *right)
{
    return jsstr_length(left) == jsstr_length(right) && !jsstr_cmp(left, right);
}