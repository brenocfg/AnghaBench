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
typedef  int /*<<< orphan*/  symbol ;
struct SN_env {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE (int /*<<< orphan*/  const*) ; 
 int eq_s_b (struct SN_env*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

extern int eq_v_b(struct SN_env * z, const symbol * p) {
    return eq_s_b(z, SIZE(p), p);
}