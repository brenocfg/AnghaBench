#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct viadev {unsigned int lastpos; unsigned int bufsize; TYPE_1__* idx_table; int /*<<< orphan*/  bufsize2; int /*<<< orphan*/  tbl_entries; } ;
struct via82xx_modem {TYPE_2__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {unsigned int size; unsigned int offset; } ;

/* Variables and functions */
 scalar_t__ check_invalid_pos (struct viadev*,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static inline unsigned int calc_linear_pos(struct via82xx_modem *chip,
					   struct viadev *viadev,
					   unsigned int idx,
					   unsigned int count)
{
	unsigned int size, res;

	size = viadev->idx_table[idx].size;
	res = viadev->idx_table[idx].offset + size - count;

	/* check the validity of the calculated position */
	if (size < count) {
		dev_err(chip->card->dev,
			"invalid via82xx_cur_ptr (size = %d, count = %d)\n",
			   (int)size, (int)count);
		res = viadev->lastpos;
	} else if (check_invalid_pos(viadev, res)) {
#ifdef POINTER_DEBUG
		dev_dbg(chip->card->dev,
			"fail: idx = %i/%i, lastpos = 0x%x, bufsize2 = 0x%x, offsize = 0x%x, size = 0x%x, count = 0x%x\n",
			idx, viadev->tbl_entries, viadev->lastpos,
		       viadev->bufsize2, viadev->idx_table[idx].offset,
		       viadev->idx_table[idx].size, count);
#endif
		if (count && size < count) {
			dev_dbg(chip->card->dev,
				"invalid via82xx_cur_ptr, using last valid pointer\n");
			res = viadev->lastpos;
		} else {
			if (! count)
				/* bogus count 0 on the DMA boundary? */
				res = viadev->idx_table[idx].offset;
			else
				/* count register returns full size
				 * when end of buffer is reached
				 */
				res = viadev->idx_table[idx].offset + size;
			if (check_invalid_pos(viadev, res)) {
				dev_dbg(chip->card->dev,
					"invalid via82xx_cur_ptr (2), using last valid pointer\n");
				res = viadev->lastpos;
			}
		}
	}
	viadev->lastpos = res; /* remember the last position */
	if (res >= viadev->bufsize)
		res -= viadev->bufsize;
	return res;
}