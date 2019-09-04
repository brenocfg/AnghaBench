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
struct v4l2_pix_format {scalar_t__ pixelformat; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {scalar_t__ pixelformat; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* formats ; 
 int /*<<< orphan*/  memset (struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iss_video_pix_to_mbus(const struct v4l2_pix_format *pix,
				  struct v4l2_mbus_framefmt *mbus)
{
	unsigned int i;

	memset(mbus, 0, sizeof(*mbus));
	mbus->width = pix->width;
	mbus->height = pix->height;

	/*
	 * Skip the last format in the loop so that it will be selected if no
	 * match is found.
	 */
	for (i = 0; i < ARRAY_SIZE(formats) - 1; ++i) {
		if (formats[i].pixelformat == pix->pixelformat)
			break;
	}

	mbus->code = formats[i].code;
	mbus->colorspace = pix->colorspace;
	mbus->field = pix->field;
}