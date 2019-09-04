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
struct vml_par {int dummy; } ;
struct vml_info {int pipe_disabled; struct vml_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  VML_DSPCCNTR ; 
 int VML_GFX_ENABLE ; 
 int VML_MDVO_VDC_I_RCOMP ; 
 int /*<<< orphan*/  VML_PIPEACONF ; 
 int /*<<< orphan*/  VML_RCOMPSTAT ; 
 int VML_READ32 (struct vml_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VML_WRITE32 (struct vml_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vml_wait_vblank (struct vml_info*) ; 

__attribute__((used)) static void vmlfb_disable_pipe(struct vml_info *vinfo)
{
	struct vml_par *par = vinfo->par;

	/* Disable the MDVO pad */
	VML_WRITE32(par, VML_RCOMPSTAT, 0);
	while (!(VML_READ32(par, VML_RCOMPSTAT) & VML_MDVO_VDC_I_RCOMP)) ;

	/* Disable display planes */
	VML_WRITE32(par, VML_DSPCCNTR,
		    VML_READ32(par, VML_DSPCCNTR) & ~VML_GFX_ENABLE);
	(void)VML_READ32(par, VML_DSPCCNTR);
	/* Wait for vblank for the disable to take effect */
	vml_wait_vblank(vinfo);

	/* Next, disable display pipes */
	VML_WRITE32(par, VML_PIPEACONF, 0);
	(void)VML_READ32(par, VML_PIPEACONF);

	vinfo->pipe_disabled = 1;
}