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
struct xt_tgdtor_param {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF_LOG_TYPE_LOG ; 
 int /*<<< orphan*/  nf_logger_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trace_tg_destroy(const struct xt_tgdtor_param *par)
{
	nf_logger_put(par->family, NF_LOG_TYPE_LOG);
}