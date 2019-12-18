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
struct TYPE_2__ {scalar_t__ (* f ) (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* l ) (struct zip_source*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ;} ;
struct zip_source {int error_source; int /*<<< orphan*/  ud; struct zip_source* src; TYPE_1__ cb; } ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 int ZIP_ER_INTERNAL ; 
 int ZIP_ER_INVAL ; 
#define  ZIP_LES_INVAL 131 
#define  ZIP_LES_LOWER 130 
#define  ZIP_LES_NONE 129 
#define  ZIP_LES_UPPER 128 
 int /*<<< orphan*/  ZIP_SOURCE_ERROR ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct zip_source*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 

void
zip_source_error(struct zip_source *src, int *ze, int *se)
{
    int e[2];

    if (src->src == NULL) {
        if (src->cb.f(src->ud, e, sizeof(e), ZIP_SOURCE_ERROR) < 0) {
            e[0] = ZIP_ER_INTERNAL;
            e[1] = 0;
        }
    }
    else {
	switch (src->error_source) {
	case ZIP_LES_NONE:
	    e[0] = e[1] = 0;
	    break;

	case ZIP_LES_INVAL:
	    e[0] = ZIP_ER_INVAL;
	    e[1] = 0;
	    break;

	case ZIP_LES_LOWER:
	    zip_source_error(src->src, ze, se);
	    return;

	case ZIP_LES_UPPER:
	    if (src->cb.l(src->src, src->ud, e, sizeof(e), ZIP_SOURCE_ERROR) < 0) {
		e[0] = ZIP_ER_INTERNAL;
		e[1] = 0;
	    }
	    break;

	default:
	    e[0] = ZIP_ER_INTERNAL;
	    e[1] = 0;
	    break;
	}
    }

    if (ze)
	*ze = e[0];
    if (se)
	*se = e[1];
}