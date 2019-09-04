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
struct iomap_dio {int flags; } ;
struct iomap {int type; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int IOMAP_DIO_WRITE ; 
#define  IOMAP_HOLE 131 
#define  IOMAP_INLINE 130 
#define  IOMAP_MAPPED 129 
#define  IOMAP_UNWRITTEN 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iomap_dio_bio_actor (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iomap_dio*,struct iomap*) ; 
 int /*<<< orphan*/  iomap_dio_hole_actor (int /*<<< orphan*/ ,struct iomap_dio*) ; 
 int /*<<< orphan*/  iomap_dio_inline_actor (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iomap_dio*,struct iomap*) ; 

__attribute__((used)) static loff_t
iomap_dio_actor(struct inode *inode, loff_t pos, loff_t length,
		void *data, struct iomap *iomap)
{
	struct iomap_dio *dio = data;

	switch (iomap->type) {
	case IOMAP_HOLE:
		if (WARN_ON_ONCE(dio->flags & IOMAP_DIO_WRITE))
			return -EIO;
		return iomap_dio_hole_actor(length, dio);
	case IOMAP_UNWRITTEN:
		if (!(dio->flags & IOMAP_DIO_WRITE))
			return iomap_dio_hole_actor(length, dio);
		return iomap_dio_bio_actor(inode, pos, length, dio, iomap);
	case IOMAP_MAPPED:
		return iomap_dio_bio_actor(inode, pos, length, dio, iomap);
	case IOMAP_INLINE:
		return iomap_dio_inline_actor(inode, pos, length, dio, iomap);
	default:
		WARN_ON_ONCE(1);
		return -EIO;
	}
}