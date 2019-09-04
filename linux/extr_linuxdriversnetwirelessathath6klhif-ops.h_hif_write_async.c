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
typedef  int /*<<< orphan*/  u32 ;
struct htc_packet {int dummy; } ;
struct ath6kl {TYPE_1__* hif_ops; } ;
struct TYPE_2__ {int (* write_async ) (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct htc_packet*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HIF ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct ath6kl*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct htc_packet*) ; 

__attribute__((used)) static inline int hif_write_async(struct ath6kl *ar, u32 address, u8 *buffer,
				  u32 length, u32 request,
				  struct htc_packet *packet)
{
	ath6kl_dbg(ATH6KL_DBG_HIF,
		   "hif write async addr 0x%x buf 0x%p len %d request 0x%x\n",
		   address, buffer, length, request);

	return ar->hif_ops->write_async(ar, address, buffer, length,
					request, packet);
}