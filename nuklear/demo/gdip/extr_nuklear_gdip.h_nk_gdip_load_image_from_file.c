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
struct nk_image {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  GpImage ;

/* Variables and functions */
 scalar_t__ GdipLoadImageFromFile (int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 struct nk_image nk_gdip_image_to_nk (int /*<<< orphan*/ *) ; 
 struct nk_image nk_image_id (int /*<<< orphan*/ ) ; 

struct nk_image
nk_gdip_load_image_from_file(const WCHAR *filename)
{
    GpImage *image;
    if (GdipLoadImageFromFile(filename, &image))
        return nk_image_id(0);
    return nk_gdip_image_to_nk(image);
}