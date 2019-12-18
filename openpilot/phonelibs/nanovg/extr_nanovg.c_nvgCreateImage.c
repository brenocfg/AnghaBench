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
typedef  int /*<<< orphan*/  NVGcontext ;

/* Variables and functions */
 int nvgCreateImageRGBA (int /*<<< orphan*/ *,int,int,int,unsigned char*) ; 
 int /*<<< orphan*/  stbi_convert_iphone_png_to_rgb (int) ; 
 int /*<<< orphan*/  stbi_image_free (unsigned char*) ; 
 unsigned char* stbi_load (char const*,int*,int*,int*,int) ; 
 int /*<<< orphan*/  stbi_set_unpremultiply_on_load (int) ; 

int nvgCreateImage(NVGcontext* ctx, const char* filename, int imageFlags)
{
	int w, h, n, image;
	unsigned char* img;
	stbi_set_unpremultiply_on_load(1);
	stbi_convert_iphone_png_to_rgb(1);
	img = stbi_load(filename, &w, &h, &n, 4);
	if (img == NULL) {
//		printf("Failed to load %s - %s\n", filename, stbi_failure_reason());
		return 0;
	}
	image = nvgCreateImageRGBA(ctx, w, h, imageFlags, img);
	stbi_image_free(img);
	return image;
}