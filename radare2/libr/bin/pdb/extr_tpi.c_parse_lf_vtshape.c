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
struct TYPE_3__ {char* vt_descriptors; int count; int /*<<< orphan*/  pad; } ;
typedef  TYPE_1__ SLF_VTSHAPE ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_ALIGN (int /*<<< orphan*/ ,unsigned int,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  PEEK_READ1 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ2 (unsigned int,unsigned int,int,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  ut16 ; 
 int /*<<< orphan*/  ut8 ; 

__attribute__((used)) static int parse_lf_vtshape(SLF_VTSHAPE *lf_vtshape, unsigned char *leaf_data, unsigned int *read_bytes, unsigned int len) {
	unsigned int tmp_before_read_bytes = *read_bytes;
	unsigned int size; // in bytes;

	lf_vtshape->vt_descriptors = 0;

	READ2(*read_bytes, len, lf_vtshape->count, leaf_data, ut16);

	size = (4 * lf_vtshape->count + (lf_vtshape->count % 2) * 4) / 8;
	lf_vtshape->vt_descriptors = (char *) malloc (size);
	if (!lf_vtshape->vt_descriptors) {
		return 0;
	}
	memcpy (lf_vtshape->vt_descriptors, leaf_data, size);
	leaf_data += size;
	*read_bytes += size;

	PEEK_READ1(*read_bytes, len, lf_vtshape->pad, leaf_data, ut8);
	PAD_ALIGN (lf_vtshape->pad, *read_bytes, leaf_data, len);

	return *read_bytes - tmp_before_read_bytes;
}