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
struct bio {int dummy; } ;
typedef  enum btrfs_map_op { ____Placeholder_btrfs_map_op } btrfs_map_op ;

/* Variables and functions */
 int BTRFS_MAP_DISCARD ; 
 int BTRFS_MAP_READ ; 
 int BTRFS_MAP_WRITE ; 
#define  REQ_OP_DISCARD 130 
#define  REQ_OP_READ 129 
#define  REQ_OP_WRITE 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int bio_op (struct bio*) ; 

__attribute__((used)) static inline enum btrfs_map_op btrfs_op(struct bio *bio)
{
	switch (bio_op(bio)) {
	case REQ_OP_DISCARD:
		return BTRFS_MAP_DISCARD;
	case REQ_OP_WRITE:
		return BTRFS_MAP_WRITE;
	default:
		WARN_ON_ONCE(1);
		/* fall through */
	case REQ_OP_READ:
		return BTRFS_MAP_READ;
	}
}