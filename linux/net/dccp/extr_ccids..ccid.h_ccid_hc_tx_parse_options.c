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
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct ccid {TYPE_1__* ccid_ops; } ;
struct TYPE_2__ {int (* ccid_hc_tx_parse_options ) (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ccid_hc_tx_parse_options(struct ccid *ccid, struct sock *sk,
					   u8 pkt, u8 opt, u8 *val, u8 len)
{
	if (!ccid || !ccid->ccid_ops->ccid_hc_tx_parse_options)
		return 0;
	return ccid->ccid_ops->ccid_hc_tx_parse_options(sk, pkt, opt, val, len);
}