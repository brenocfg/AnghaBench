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
typedef  int /*<<< orphan*/  gdIOCtx ;
struct TYPE_3__ {int /*<<< orphan*/  off; int /*<<< orphan*/  reserved2; int /*<<< orphan*/  reserved1; int /*<<< orphan*/  size; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ bmp_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  gdGetIntLSB (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdGetWordLSB (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bmp_read_header(gdIOCtx *infile, bmp_hdr_t *hdr)
{
	if(
	    !gdGetWordLSB(&hdr->magic, infile) ||
	    !gdGetIntLSB(&hdr->size, infile) ||
	    !gdGetWordLSB(&hdr->reserved1, infile) ||
	    !gdGetWordLSB(&hdr->reserved2 , infile) ||
	    !gdGetIntLSB(&hdr->off , infile)
	) {
		return 1;
	}
	return 0;
}