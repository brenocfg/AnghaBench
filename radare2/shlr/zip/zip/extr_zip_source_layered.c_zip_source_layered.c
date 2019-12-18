#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zip_source_layered_callback ;
struct TYPE_2__ {int /*<<< orphan*/  l; } ;
struct zip_source {void* ud; TYPE_1__ cb; struct zip_source* src; } ;
struct zip {int dummy; } ;

/* Variables and functions */
 struct zip_source* _zip_source_new (struct zip*) ; 

struct zip_source *
zip_source_layered(struct zip *za, struct zip_source *src,
		   zip_source_layered_callback cb, void *ud)
{
    struct zip_source *zs;

    if (za == NULL)
	return NULL;

    if ((zs=_zip_source_new(za)) == NULL)
	return NULL;

    zs->src = src;
    zs->cb.l = cb;
    zs->ud = ud;
    
    return zs;
}