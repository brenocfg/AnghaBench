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
struct SN_env {int dummy; } ;

/* Variables and functions */
 int slice_from_s (struct SN_env*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

extern int slice_del(struct SN_env * z) {
    return slice_from_s(z, 0, 0);
}