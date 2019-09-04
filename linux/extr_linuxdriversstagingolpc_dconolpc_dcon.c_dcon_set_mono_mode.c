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
struct dcon_priv {int mono; int disp_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCON_REG_MODE ; 
 int MODE_COL_AA ; 
 int MODE_CSWIZZLE ; 
 int MODE_MONO_LUMA ; 
 int /*<<< orphan*/  dcon_write (struct dcon_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dcon_set_mono_mode(struct dcon_priv *dcon, bool enable_mono)
{
	if (dcon->mono == enable_mono)
		return 0;

	dcon->mono = enable_mono;

	if (enable_mono) {
		dcon->disp_mode &= ~(MODE_CSWIZZLE | MODE_COL_AA);
		dcon->disp_mode |= MODE_MONO_LUMA;
	} else {
		dcon->disp_mode &= ~(MODE_MONO_LUMA);
		dcon->disp_mode |= MODE_CSWIZZLE | MODE_COL_AA;
	}

	dcon_write(dcon, DCON_REG_MODE, dcon->disp_mode);
	return 0;
}