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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  tmsize_t ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */

void
_TIFFNoPostDecode(TIFF* tif, uint8* buf, tmsize_t cc)
{
    (void) tif; (void) buf; (void) cc;
}