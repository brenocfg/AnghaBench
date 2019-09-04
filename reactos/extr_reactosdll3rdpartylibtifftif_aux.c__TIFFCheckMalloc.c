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
typedef  int /*<<< orphan*/  tmsize_t ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 void* _TIFFCheckRealloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

void*
_TIFFCheckMalloc(TIFF* tif, tmsize_t nmemb, tmsize_t elem_size, const char* what)
{
	return _TIFFCheckRealloc(tif, NULL, nmemb, elem_size, what);  
}