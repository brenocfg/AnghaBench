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
struct jpeg_compress_struct {int restart_interval; int restart_in_rows; int num_components; TYPE_2__* comp_info; TYPE_1__* master; int /*<<< orphan*/  dct_method; void* arith_code; void* optimize_coding; int /*<<< orphan*/  input_components; int /*<<< orphan*/  in_color_space; } ;
struct TYPE_4__ {int h_samp_factor; int v_samp_factor; } ;
struct TYPE_3__ {scalar_t__ compress_profile; } ;

/* Variables and functions */
 scalar_t__ JCP_FASTEST ; 
 scalar_t__ JCP_MAX_COMPRESSION ; 
 int /*<<< orphan*/  JCS_GRAYSCALE ; 
 int /*<<< orphan*/  JCS_YCCK ; 
 int /*<<< orphan*/  JCS_YCbCr ; 
 int /*<<< orphan*/  JDCT_FASTEST ; 
 int /*<<< orphan*/  JDCT_ISLOW ; 
 int TJFLAG_ACCURATEDCT ; 
 int TJFLAG_PROGRESSIVE ; 
 int TJPF_CMYK ; 
 int TJSAMP_GRAY ; 
 void* TRUE ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  jpeg_set_colorspace (struct jpeg_compress_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_set_defaults (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_set_quality (struct jpeg_compress_struct*,int,void*) ; 
 int /*<<< orphan*/  jpeg_simple_progression (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/ * pf2cs ; 
 int sscanf (char*,char*,int*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int* tjMCUHeight ; 
 int* tjMCUWidth ; 
 int /*<<< orphan*/ * tjPixelSize ; 
 char toupper (char) ; 

__attribute__((used)) static int setCompDefaults(struct jpeg_compress_struct *cinfo, int pixelFormat,
                           int subsamp, int jpegQual, int flags)
{
	int retval=0;
	char *env=NULL;

  cinfo->in_color_space = pf2cs[pixelFormat];
	cinfo->input_components=tjPixelSize[pixelFormat];
	if((env=getenv("TJ_REVERT"))!=NULL && strlen(env)>0 && !strcmp(env, "1"))
		cinfo->master->compress_profile=JCP_FASTEST;
	jpeg_set_defaults(cinfo);

#ifndef NO_GETENV
  if ((env = getenv("TJ_OPTIMIZE")) != NULL && strlen(env) > 0 &&
      !strcmp(env, "1"))
		cinfo->optimize_coding=TRUE;
  if ((env = getenv("TJ_ARITHMETIC")) != NULL && strlen(env) > 0 &&
      !strcmp(env, "1"))
		cinfo->arith_code=TRUE;
  if ((env = getenv("TJ_RESTART")) != NULL && strlen(env) > 0) {
    int temp = -1;
    char tempc = 0;

    if (sscanf(env, "%d%c", &temp, &tempc) >= 1 && temp >= 0 &&
        temp <= 65535) {
      if (toupper(tempc) == 'B') {
				cinfo->restart_interval=temp;
				cinfo->restart_in_rows=0;
      } else
				cinfo->restart_in_rows=temp;
		}
	}
#endif

  if (jpegQual >= 0) {
		jpeg_set_quality(cinfo, jpegQual, TRUE);
    if (jpegQual >= 96 || flags & TJFLAG_ACCURATEDCT)
      cinfo->dct_method = JDCT_ISLOW;
    else
      cinfo->dct_method = JDCT_FASTEST;
	}
	if(subsamp==TJSAMP_GRAY)
		jpeg_set_colorspace(cinfo, JCS_GRAYSCALE);
	else if(pixelFormat==TJPF_CMYK)
		jpeg_set_colorspace(cinfo, JCS_YCCK);
  else
    jpeg_set_colorspace(cinfo, JCS_YCbCr);

  if (flags & TJFLAG_PROGRESSIVE)
    jpeg_simple_progression(cinfo);
#ifndef NO_GETENV
  else if ((env = getenv("TJ_PROGRESSIVE")) != NULL && strlen(env) > 0 &&
           !strcmp(env, "1"))
		jpeg_simple_progression(cinfo);
#endif

	/* Set scan pattern again as colorspace might have changed */
	if(cinfo->master->compress_profile == JCP_MAX_COMPRESSION)
		jpeg_simple_progression(cinfo);

	cinfo->comp_info[0].h_samp_factor=tjMCUWidth[subsamp]/8;
	cinfo->comp_info[1].h_samp_factor=1;
	cinfo->comp_info[2].h_samp_factor=1;
	if(cinfo->num_components>3)
		cinfo->comp_info[3].h_samp_factor=tjMCUWidth[subsamp]/8;
	cinfo->comp_info[0].v_samp_factor=tjMCUHeight[subsamp]/8;
	cinfo->comp_info[1].v_samp_factor=1;
	cinfo->comp_info[2].v_samp_factor=1;
	if(cinfo->num_components>3)
		cinfo->comp_info[3].v_samp_factor=tjMCUHeight[subsamp]/8;

	return retval;
}