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
typedef  int /*<<< orphan*/  u16 ;
struct send_ctx {int dummy; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_timespec {int dummy; } ;
typedef  int /*<<< orphan*/  bts ;

/* Variables and functions */
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,struct btrfs_timespec*,unsigned long,int) ; 
 int tlv_put (struct send_ctx*,int /*<<< orphan*/ ,struct btrfs_timespec*,int) ; 

__attribute__((used)) static int tlv_put_btrfs_timespec(struct send_ctx *sctx, u16 attr,
				  struct extent_buffer *eb,
				  struct btrfs_timespec *ts)
{
	struct btrfs_timespec bts;
	read_extent_buffer(eb, &bts, (unsigned long)ts, sizeof(bts));
	return tlv_put(sctx, attr, &bts, sizeof(bts));
}