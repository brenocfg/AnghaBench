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
struct perf_ctx {int dummy; } ;
struct ntb_dev {int dummy; } ;
struct ntb_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct perf_ctx*) ; 
 int PTR_ERR (struct perf_ctx*) ; 
 struct perf_ctx* perf_create_data (struct ntb_dev*) ; 
 int perf_enable_service (struct perf_ctx*) ; 
 int perf_init_peers (struct perf_ctx*) ; 
 int perf_init_service (struct perf_ctx*) ; 
 int /*<<< orphan*/  perf_init_threads (struct perf_ctx*) ; 
 int /*<<< orphan*/  perf_setup_dbgfs (struct perf_ctx*) ; 

__attribute__((used)) static int perf_probe(struct ntb_client *client, struct ntb_dev *ntb)
{
	struct perf_ctx *perf;
	int ret;

	perf = perf_create_data(ntb);
	if (IS_ERR(perf))
		return PTR_ERR(perf);

	ret = perf_init_peers(perf);
	if (ret)
		return ret;

	perf_init_threads(perf);

	ret = perf_init_service(perf);
	if (ret)
		return ret;

	ret = perf_enable_service(perf);
	if (ret)
		return ret;

	perf_setup_dbgfs(perf);

	return 0;
}