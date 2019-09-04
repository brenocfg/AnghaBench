#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  norm; int /*<<< orphan*/  priv; TYPE_1__* functions; } ;
typedef  TYPE_2__ tvi_handle_t ;
struct TYPE_7__ {scalar_t__ (* control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,char*) ; 
 scalar_t__ TVI_CONTROL_TRUE ; 
 int /*<<< orphan*/  TVI_CONTROL_TUN_SET_NORM ; 
 int /*<<< orphan*/  norm_from_string (TYPE_2__*,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int tv_set_norm(tvi_handle_t *tvh, char* norm)
{
    tvh->norm = norm_from_string(tvh, norm);

    MP_VERBOSE(tvh, "Selected norm : %s\n", norm);
    if (tvh->functions->control(tvh->priv, TVI_CONTROL_TUN_SET_NORM, &tvh->norm) != TVI_CONTROL_TRUE) {
        MP_ERR(tvh, "Error: Cannot set norm!\n");
        return 0;
    }
    return 1;
}