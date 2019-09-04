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
typedef  size_t tmsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  _TIFFfree (void*) ; 
 scalar_t__ _TIFFmalloc (size_t) ; 
 int /*<<< orphan*/  _TIFFmemcpy (void*,void*,size_t) ; 

__attribute__((used)) static void
setByteArray(void** vpp, void* vp, size_t nmemb, size_t elem_size)
{
	if (*vpp) {
		_TIFFfree(*vpp);
		*vpp = 0;
	}
	if (vp) {
		tmsize_t bytes = (tmsize_t)(nmemb * elem_size);
		if (elem_size && bytes / elem_size == nmemb)
			*vpp = (void*) _TIFFmalloc(bytes);
		if (*vpp)
			_TIFFmemcpy(*vpp, vp, bytes);
	}
}