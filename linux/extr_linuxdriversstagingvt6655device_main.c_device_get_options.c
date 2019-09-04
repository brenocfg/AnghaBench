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
struct vnt_options {int /*<<< orphan*/  bbp_type; int /*<<< orphan*/  long_retry; int /*<<< orphan*/  short_retry; int /*<<< orphan*/  int_works; int /*<<< orphan*/ * tx_descs; int /*<<< orphan*/  rx_descs1; int /*<<< orphan*/  rx_descs0; } ;
struct vnt_private {struct vnt_options opts; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBP_TYPE_DEF ; 
 int /*<<< orphan*/  INT_WORKS_DEF ; 
 int /*<<< orphan*/  LONG_RETRY_DEF ; 
 int /*<<< orphan*/  RX_DESC_DEF0 ; 
 int /*<<< orphan*/  RX_DESC_DEF1 ; 
 int /*<<< orphan*/  SHORT_RETRY_DEF ; 
 int /*<<< orphan*/  TX_DESC_DEF0 ; 
 int /*<<< orphan*/  TX_DESC_DEF1 ; 

__attribute__((used)) static void device_get_options(struct vnt_private *priv)
{
	struct vnt_options *opts = &priv->opts;

	opts->rx_descs0 = RX_DESC_DEF0;
	opts->rx_descs1 = RX_DESC_DEF1;
	opts->tx_descs[0] = TX_DESC_DEF0;
	opts->tx_descs[1] = TX_DESC_DEF1;
	opts->int_works = INT_WORKS_DEF;

	opts->short_retry = SHORT_RETRY_DEF;
	opts->long_retry = LONG_RETRY_DEF;
	opts->bbp_type = BBP_TYPE_DEF;
}