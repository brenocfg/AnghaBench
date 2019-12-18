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
struct scaler_config {scalar_t__ radius; scalar_t__ clamp; int /*<<< orphan*/  window; int /*<<< orphan*/  kernel; } ;

/* Variables and functions */
 scalar_t__ scaler_fun_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool scaler_conf_eq(struct scaler_config a, struct scaler_config b)
{
    // Note: antiring isn't compared because it doesn't affect LUT
    // generation
    return scaler_fun_eq(a.kernel, b.kernel) &&
           scaler_fun_eq(a.window, b.window) &&
           a.radius == b.radius &&
           a.clamp == b.clamp;
}