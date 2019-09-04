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
struct fib_info {TYPE_1__* fib_metrics; int /*<<< orphan*/  fib_net; } ;
struct fib_config {int /*<<< orphan*/  fc_mx_len; int /*<<< orphan*/  fc_mx; } ;
struct TYPE_2__ {int /*<<< orphan*/  metrics; } ;

/* Variables and functions */
 int ip_metrics_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fib_convert_metrics(struct fib_info *fi, const struct fib_config *cfg)
{
	return ip_metrics_convert(fi->fib_net, cfg->fc_mx, cfg->fc_mx_len,
				  fi->fib_metrics->metrics);
}