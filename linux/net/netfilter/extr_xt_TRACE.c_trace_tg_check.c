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
struct xt_tgchk_param {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  NF_LOG_TYPE_LOG ; 
 int nf_logger_find_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trace_tg_check(const struct xt_tgchk_param *par)
{
	return nf_logger_find_get(par->family, NF_LOG_TYPE_LOG);
}