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
typedef  scalar_t__ uint ;
struct xfs_buf_log_item {int bli_format_count; TYPE_1__* bli_formats; struct xfs_buf* bli_buf; } ;
struct xfs_buf {TYPE_2__* b_maps; } ;
struct TYPE_4__ {int /*<<< orphan*/  bm_len; } ;
struct TYPE_3__ {int /*<<< orphan*/ * blf_data_map; } ;

/* Variables and functions */
 scalar_t__ BBTOB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_item_log_segment (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

void
xfs_buf_item_log(
	struct xfs_buf_log_item	*bip,
	uint			first,
	uint			last)
{
	int			i;
	uint			start;
	uint			end;
	struct xfs_buf		*bp = bip->bli_buf;

	/*
	 * walk each buffer segment and mark them dirty appropriately.
	 */
	start = 0;
	for (i = 0; i < bip->bli_format_count; i++) {
		if (start > last)
			break;
		end = start + BBTOB(bp->b_maps[i].bm_len) - 1;

		/* skip to the map that includes the first byte to log */
		if (first > end) {
			start += BBTOB(bp->b_maps[i].bm_len);
			continue;
		}

		/*
		 * Trim the range to this segment and mark it in the bitmap.
		 * Note that we must convert buffer offsets to segment relative
		 * offsets (e.g., the first byte of each segment is byte 0 of
		 * that segment).
		 */
		if (first < start)
			first = start;
		if (end > last)
			end = last;
		xfs_buf_item_log_segment(first - start, end - start,
					 &bip->bli_formats[i].blf_data_map[0]);

		start += BBTOB(bp->b_maps[i].bm_len);
	}
}