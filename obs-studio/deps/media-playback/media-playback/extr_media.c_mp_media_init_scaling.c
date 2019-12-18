#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* decoder; } ;
struct TYPE_7__ {int /*<<< orphan*/  scale_format; TYPE_2__ v; int /*<<< orphan*/  scale_linesizes; int /*<<< orphan*/  scale_pic; int /*<<< orphan*/  swscale; } ;
typedef  TYPE_3__ mp_media_t ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  color_range; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXED_1_0 ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  SWS_FAST_BILINEAR ; 
 int av_image_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int get_sws_colorspace (int /*<<< orphan*/ ) ; 
 int get_sws_range (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sws_getCachedContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int* sws_getCoefficients (int) ; 
 int /*<<< orphan*/  sws_setColorspaceDetails (int /*<<< orphan*/ ,int const*,int,int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mp_media_init_scaling(mp_media_t *m)
{
	int space = get_sws_colorspace(m->v.decoder->colorspace);
	int range = get_sws_range(m->v.decoder->color_range);
	const int *coeff = sws_getCoefficients(space);

	m->swscale = sws_getCachedContext(NULL, m->v.decoder->width,
					  m->v.decoder->height,
					  m->v.decoder->pix_fmt,
					  m->v.decoder->width,
					  m->v.decoder->height, m->scale_format,
					  SWS_FAST_BILINEAR, NULL, NULL, NULL);
	if (!m->swscale) {
		blog(LOG_WARNING, "MP: Failed to initialize scaler");
		return false;
	}

	sws_setColorspaceDetails(m->swscale, coeff, range, coeff, range, 0,
				 FIXED_1_0, FIXED_1_0);

	int ret = av_image_alloc(m->scale_pic, m->scale_linesizes,
				 m->v.decoder->width, m->v.decoder->height,
				 m->scale_format, 1);
	if (ret < 0) {
		blog(LOG_WARNING, "MP: Failed to create scale pic data");
		return false;
	}

	return true;
}