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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct send_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_UUID_SIZE ; 
 int tlv_put (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tlv_put_uuid(struct send_ctx *sctx, u16 attr,
			const u8 *uuid)
{
	return tlv_put(sctx, attr, uuid, BTRFS_UUID_SIZE);
}