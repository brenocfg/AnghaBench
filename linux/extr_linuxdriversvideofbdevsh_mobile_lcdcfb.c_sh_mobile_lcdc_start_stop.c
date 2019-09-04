#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_mobile_lcdc_priv {TYPE_1__* ch; } ;
struct TYPE_3__ {int enabled; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned long LDCNT2R_DO ; 
 int /*<<< orphan*/  LDPMR ; 
 unsigned long LDPMR_LPS ; 
 int /*<<< orphan*/  _LDCNT2R ; 
 int /*<<< orphan*/  _LDDCKSTPR ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int lcdc_read (struct sh_mobile_lcdc_priv*,int /*<<< orphan*/ ) ; 
 unsigned long lcdc_read_chan (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (struct sh_mobile_lcdc_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sh_mobile_lcdc_start_stop(struct sh_mobile_lcdc_priv *priv,
				      int start)
{
	unsigned long tmp = lcdc_read(priv, _LDCNT2R);
	int k;

	/* start or stop the lcdc */
	if (start)
		lcdc_write(priv, _LDCNT2R, tmp | LDCNT2R_DO);
	else
		lcdc_write(priv, _LDCNT2R, tmp & ~LDCNT2R_DO);

	/* wait until power is applied/stopped on all channels */
	for (k = 0; k < ARRAY_SIZE(priv->ch); k++)
		if (lcdc_read(priv, _LDCNT2R) & priv->ch[k].enabled)
			while (1) {
				tmp = lcdc_read_chan(&priv->ch[k], LDPMR)
				    & LDPMR_LPS;
				if (start && tmp == LDPMR_LPS)
					break;
				if (!start && tmp == 0)
					break;
				cpu_relax();
			}

	if (!start)
		lcdc_write(priv, _LDDCKSTPR, 1); /* stop dotclock */
}