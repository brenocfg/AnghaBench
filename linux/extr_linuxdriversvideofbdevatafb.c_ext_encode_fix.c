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
struct fb_fix_screeninfo {int type; int visual; int type_aux; int /*<<< orphan*/  line_length; scalar_t__ ywrapstep; scalar_t__ ypanstep; scalar_t__ xpanstep; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  id; } ;
struct atafb_par {int /*<<< orphan*/  next_line; } ;

/* Variables and functions */
#define  FB_TYPE_INTERLEAVED_PLANES 130 
#define  FB_TYPE_PACKED_PIXELS 129 
#define  FB_TYPE_PLANES 128 
 int FB_VISUAL_MONO01 ; 
 int FB_VISUAL_MONO10 ; 
 int FB_VISUAL_PSEUDOCOLOR ; 
 int FB_VISUAL_STATIC_PSEUDOCOLOR ; 
 int FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  external_addr ; 
 int external_depth ; 
 int /*<<< orphan*/  external_len ; 
 int external_pmode ; 
 scalar_t__ external_vgaiobase ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ext_encode_fix(struct fb_fix_screeninfo *fix, struct atafb_par *par)
{
	strcpy(fix->id, "Unknown Extern");
	fix->smem_start = external_addr;
	fix->smem_len = PAGE_ALIGN(external_len);
	if (external_depth == 1) {
		fix->type = FB_TYPE_PACKED_PIXELS;
		/* The letters 'n' and 'i' in the "atavideo=external:" stand
		 * for "normal" and "inverted", rsp., in the monochrome case */
		fix->visual =
			(external_pmode == FB_TYPE_INTERLEAVED_PLANES ||
			 external_pmode == FB_TYPE_PACKED_PIXELS) ?
				FB_VISUAL_MONO10 : FB_VISUAL_MONO01;
	} else {
		/* Use STATIC if we don't know how to access color registers */
		int visual = external_vgaiobase ?
					 FB_VISUAL_PSEUDOCOLOR :
					 FB_VISUAL_STATIC_PSEUDOCOLOR;
		switch (external_pmode) {
		case -1:		/* truecolor */
			fix->type = FB_TYPE_PACKED_PIXELS;
			fix->visual = FB_VISUAL_TRUECOLOR;
			break;
		case FB_TYPE_PACKED_PIXELS:
			fix->type = FB_TYPE_PACKED_PIXELS;
			fix->visual = visual;
			break;
		case FB_TYPE_PLANES:
			fix->type = FB_TYPE_PLANES;
			fix->visual = visual;
			break;
		case FB_TYPE_INTERLEAVED_PLANES:
			fix->type = FB_TYPE_INTERLEAVED_PLANES;
			fix->type_aux = 2;
			fix->visual = visual;
			break;
		}
	}
	fix->xpanstep = 0;
	fix->ypanstep = 0;
	fix->ywrapstep = 0;
	fix->line_length = par->next_line;
	return 0;
}