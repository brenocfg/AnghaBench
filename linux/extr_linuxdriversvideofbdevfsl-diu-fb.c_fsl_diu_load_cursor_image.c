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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct mfb_info {struct fsl_diu_data* parent; } ;
struct fsl_diu_data {int /*<<< orphan*/ * cursor; } ;
struct fb_info {struct mfb_info* par; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (unsigned int,int) ; 
 int /*<<< orphan*/  MAX_CURS ; 
 int be32_to_cpup (void const*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_diu_load_cursor_image(struct fb_info *info,
	const void *image, uint16_t bg, uint16_t fg,
	unsigned int width, unsigned int height)
{
	struct mfb_info *mfbi = info->par;
	struct fsl_diu_data *data = mfbi->parent;
	__le16 *cursor = data->cursor;
	__le16 _fg = cpu_to_le16(fg);
	__le16 _bg = cpu_to_le16(bg);
	unsigned int h, w;

	for (h = 0; h < height; h++) {
		uint32_t mask = 1 << 31;
		uint32_t line = be32_to_cpup(image);

		for (w = 0; w < width; w++) {
			cursor[w] = (line & mask) ? _fg : _bg;
			mask >>= 1;
		}

		cursor += MAX_CURS;
		image += DIV_ROUND_UP(width, 8);
	}
}