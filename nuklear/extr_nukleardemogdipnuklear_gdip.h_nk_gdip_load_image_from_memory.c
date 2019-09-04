#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nk_image {int dummy; } ;
typedef  int /*<<< orphan*/  nk_uint ;
struct TYPE_7__ {TYPE_1__* lpVtbl; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* Release ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ IStream ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ GdipLoadImageFromStream (TYPE_2__*,int /*<<< orphan*/ **) ; 
 TYPE_2__* SHCreateMemStream (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct nk_image nk_gdip_image_to_nk (int /*<<< orphan*/ *) ; 
 struct nk_image nk_image_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

struct nk_image
nk_gdip_load_image_from_memory(const void *membuf, nk_uint membufSize)
{
    GpImage* image;
    GpStatus status;
    IStream *stream = SHCreateMemStream((const BYTE*)membuf, membufSize);
    if (!stream)
        return nk_image_id(0);
    
    status = GdipLoadImageFromStream(stream, &image);
    stream->lpVtbl->Release(stream);

    if (status)
        return nk_image_id(0);

    return nk_gdip_image_to_nk(image);
}