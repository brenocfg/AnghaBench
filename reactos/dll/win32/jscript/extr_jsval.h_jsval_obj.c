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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;

/* Variables and functions */
 int /*<<< orphan*/  jsval_disp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_disp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline jsval_t jsval_obj(jsdisp_t *obj)
{
    return jsval_disp(to_disp(obj));
}