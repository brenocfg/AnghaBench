#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  enum gs_color_format { ____Placeholder_gs_color_format } gs_color_format ;
struct TYPE_16__ {scalar_t__ severity; int /*<<< orphan*/  reason; } ;
struct TYPE_15__ {size_t magick_columns; size_t magick_rows; } ;
struct TYPE_14__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ ImageInfo ;
typedef  TYPE_2__ Image ;
typedef  TYPE_3__ ExceptionInfo ;

/* Variables and functions */
 TYPE_3__* AcquireExceptionInfo () ; 
 int /*<<< orphan*/  CharPixel ; 
 TYPE_1__* CloneImageInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyExceptionInfo (TYPE_3__*) ; 
 int /*<<< orphan*/  DestroyImage (TYPE_2__*) ; 
 int /*<<< orphan*/  DestroyImageInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  ExportImagePixels (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int GS_BGRA ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 TYPE_2__* ReadImage (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ UndefinedException ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bmalloc (size_t) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

uint8_t *gs_create_texture_file_data(const char *file,
				     enum gs_color_format *format,
				     uint32_t *cx_out, uint32_t *cy_out)
{
	uint8_t *data = NULL;
	ImageInfo *info;
	ExceptionInfo *exception;
	Image *image;

	if (!file || !*file)
		return NULL;

	info = CloneImageInfo(NULL);
	exception = AcquireExceptionInfo();

	strcpy(info->filename, file);
	image = ReadImage(info, exception);
	if (image) {
		size_t cx = image->magick_columns;
		size_t cy = image->magick_rows;
		data = bmalloc(cx * cy * 4);

		ExportImagePixels(image, 0, 0, cx, cy, "BGRA", CharPixel, data,
				  exception);
		if (exception->severity != UndefinedException) {
			blog(LOG_WARNING,
			     "magickcore warning/error getting "
			     "pixels from file '%s': %s",
			     file, exception->reason);
			bfree(data);
			data = NULL;
		}

		*format = GS_BGRA;
		*cx_out = (uint32_t)cx;
		*cy_out = (uint32_t)cy;
		DestroyImage(image);

	} else if (exception->severity != UndefinedException) {
		blog(LOG_WARNING,
		     "magickcore warning/error reading file "
		     "'%s': %s",
		     file, exception->reason);
	}

	DestroyImageInfo(info);
	DestroyExceptionInfo(exception);

	return data;
}