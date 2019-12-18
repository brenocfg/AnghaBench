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
typedef  int /*<<< orphan*/  PullFilter ;
typedef  void PGP_CFB ;

/* Variables and functions */

__attribute__((used)) static int
decrypt_init(void **priv_p, void *arg, PullFilter *src)
{
	PGP_CFB    *cfb = arg;

	*priv_p = cfb;

	/* we need to write somewhere, so ask for a buffer */
	return 4096;
}