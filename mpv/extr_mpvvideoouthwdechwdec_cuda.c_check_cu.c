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
struct ra_hwdec {struct cuda_hw_priv* priv; } ;
struct cuda_hw_priv {TYPE_1__* cu; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cuGetErrorString ) (int /*<<< orphan*/ ,char const**) ;int /*<<< orphan*/  (* cuGetErrorName ) (int /*<<< orphan*/ ,char const**) ;} ;
typedef  int /*<<< orphan*/  CUresult ;

/* Variables and functions */
 int /*<<< orphan*/  CUDA_SUCCESS ; 
 int /*<<< orphan*/  MP_ERR (struct ra_hwdec const*,char*,...) ; 
 int /*<<< orphan*/  MP_TRACE (struct ra_hwdec const*,char*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char const**) ; 

int check_cu(const struct ra_hwdec *hw, CUresult err, const char *func)
{
    const char *err_name;
    const char *err_string;

    struct cuda_hw_priv *p = hw->priv;

    MP_TRACE(hw, "Calling %s\n", func);

    if (err == CUDA_SUCCESS)
        return 0;

    p->cu->cuGetErrorName(err, &err_name);
    p->cu->cuGetErrorString(err, &err_string);

    MP_ERR(hw, "%s failed", func);
    if (err_name && err_string)
        MP_ERR(hw, " -> %s: %s", err_name, err_string);
    MP_ERR(hw, "\n");

    return -1;
}