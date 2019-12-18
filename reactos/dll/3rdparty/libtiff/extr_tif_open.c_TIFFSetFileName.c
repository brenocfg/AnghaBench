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
struct TYPE_3__ {char* tif_name; } ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */

const char *
TIFFSetFileName(TIFF* tif, const char *name)
{
	const char* old_name = tif->tif_name;
	tif->tif_name = (char *)name;
	return (old_name);
}