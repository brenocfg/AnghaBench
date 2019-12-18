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
typedef  scalar_t__ zip_int32_t ;
typedef  int /*<<< orphan*/ * zip_compression_implementation ;

/* Variables and functions */
 scalar_t__ ZIP_CM_DEFLATE ; 
 scalar_t__ ZIP_CM_IS_DEFAULT (scalar_t__) ; 
 int /*<<< orphan*/ * zip_source_deflate ; 

zip_compression_implementation
_zip_get_compression_implementation(zip_int32_t cm)
{
    if (cm == ZIP_CM_DEFLATE || ZIP_CM_IS_DEFAULT(cm))
	return zip_source_deflate;
    return NULL;
}