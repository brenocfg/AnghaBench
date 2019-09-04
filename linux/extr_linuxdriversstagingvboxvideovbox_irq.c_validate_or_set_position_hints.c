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
typedef  int u16 ;
struct vbva_modehint {int dx; int dy; int cx; int cy; scalar_t__ enabled; } ;
struct vbox_private {int num_crtcs; struct vbva_modehint* last_mode_hints; } ;

/* Variables and functions */

__attribute__((used)) static void validate_or_set_position_hints(struct vbox_private *vbox)
{
	struct vbva_modehint *hintsi, *hintsj;
	bool valid = true;
	u16 currentx = 0;
	int i, j;

	for (i = 0; i < vbox->num_crtcs; ++i) {
		for (j = 0; j < i; ++j) {
			hintsi = &vbox->last_mode_hints[i];
			hintsj = &vbox->last_mode_hints[j];

			if (hintsi->enabled && hintsj->enabled) {
				if (hintsi->dx >= 0xffff ||
				    hintsi->dy >= 0xffff ||
				    hintsj->dx >= 0xffff ||
				    hintsj->dy >= 0xffff ||
				    (hintsi->dx <
					hintsj->dx + (hintsj->cx & 0x8fff) &&
				     hintsi->dx + (hintsi->cx & 0x8fff) >
					hintsj->dx) ||
				    (hintsi->dy <
					hintsj->dy + (hintsj->cy & 0x8fff) &&
				     hintsi->dy + (hintsi->cy & 0x8fff) >
					hintsj->dy))
					valid = false;
			}
		}
	}
	if (!valid)
		for (i = 0; i < vbox->num_crtcs; ++i) {
			if (vbox->last_mode_hints[i].enabled) {
				vbox->last_mode_hints[i].dx = currentx;
				vbox->last_mode_hints[i].dy = 0;
				currentx +=
				    vbox->last_mode_hints[i].cx & 0x8fff;
			}
		}
}