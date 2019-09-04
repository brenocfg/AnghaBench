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
typedef  int /*<<< orphan*/  u32 ;
struct mite_channel {int /*<<< orphan*/  channel; struct mite* mite; } ;
struct mite {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ MITE_DAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static u32 mite_device_bytes_transferred(struct mite_channel *mite_chan)
{
	struct mite *mite = mite_chan->mite;

	return readl(mite->mmio + MITE_DAR(mite_chan->channel));
}