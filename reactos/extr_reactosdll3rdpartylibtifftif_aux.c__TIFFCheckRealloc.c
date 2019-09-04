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
typedef  int tmsize_t ;
struct TYPE_3__ {int /*<<< orphan*/  tif_name; int /*<<< orphan*/  tif_clientdata; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,long,long) ; 
 void* _TIFFrealloc (void*,int) ; 

void*
_TIFFCheckRealloc(TIFF* tif, void* buffer,
		  tmsize_t nmemb, tmsize_t elem_size, const char* what)
{
	void* cp = NULL;
	tmsize_t bytes = nmemb * elem_size;

	/*
	 * XXX: Check for integer overflow.
	 */
	if (nmemb && elem_size && bytes / elem_size == nmemb)
		cp = _TIFFrealloc(buffer, bytes);

	if (cp == NULL) {
		TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
			     "Failed to allocate memory for %s "
			     "(%ld elements of %ld bytes each)",
			     what,(long) nmemb, (long) elem_size);
	}

	return cp;
}