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
typedef  scalar_t__ uint16 ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 scalar_t__ COMPRESSION_CCITTFAX3 ; 
 scalar_t__ COMPRESSION_CCITTFAX4 ; 
 scalar_t__ COMPRESSION_CCITTRLE ; 
 scalar_t__ COMPRESSION_CCITTRLEW ; 
 int /*<<< orphan*/  TIFFGetField (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TIFFTAG_COMPRESSION ; 

__attribute__((used)) static int
isCCITTCompression(TIFF* tif)
{
    uint16 compress;
    TIFFGetField(tif, TIFFTAG_COMPRESSION, &compress);
    return (compress == COMPRESSION_CCITTFAX3 ||
	    compress == COMPRESSION_CCITTFAX4 ||
	    compress == COMPRESSION_CCITTRLE ||
	    compress == COMPRESSION_CCITTRLEW);
}