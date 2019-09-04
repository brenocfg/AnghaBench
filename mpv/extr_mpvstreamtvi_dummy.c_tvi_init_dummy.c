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
typedef  int /*<<< orphan*/  tvi_handle_t ;
typedef  int /*<<< orphan*/  tv_param_t ;
struct mp_log {int dummy; } ;
typedef  int /*<<< orphan*/  priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  functions ; 
 int /*<<< orphan*/ * tv_new_handle (int,struct mp_log*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tvi_handle_t *tvi_init_dummy(struct mp_log *log, tv_param_t* tv_param)
{
    return tv_new_handle(sizeof(priv_t), log, &functions);
}