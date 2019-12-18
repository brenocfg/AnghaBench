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
struct TYPE_2__ {int /*<<< orphan*/  sndbuf_desc; int /*<<< orphan*/  lgr; } ;
struct smc_sock {TYPE_1__ conn; } ;

/* Variables and functions */
 int __smc_buf_create (struct smc_sock*,int,int) ; 
 int /*<<< orphan*/  smc_buf_free (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int smc_buf_create(struct smc_sock *smc, bool is_smcd)
{
	int rc;

	/* create send buffer */
	rc = __smc_buf_create(smc, is_smcd, false);
	if (rc)
		return rc;
	/* create rmb */
	rc = __smc_buf_create(smc, is_smcd, true);
	if (rc)
		smc_buf_free(smc->conn.lgr, false, smc->conn.sndbuf_desc);
	return rc;
}