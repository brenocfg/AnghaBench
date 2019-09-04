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
struct TYPE_3__ {unsigned int* arg_type; int count; int /*<<< orphan*/  pad; } ;
typedef  TYPE_1__ SLF_ARGLIST ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_ALIGN (int /*<<< orphan*/ ,unsigned int,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  PEEK_READ1 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ4 (unsigned int,unsigned int,int,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned char*,int) ; 
 int /*<<< orphan*/  ut32 ; 
 int /*<<< orphan*/  ut8 ; 

__attribute__((used)) static int parse_lf_arglist(SLF_ARGLIST *lf_arglist, unsigned char *leaf_data, unsigned int *read_bytes, unsigned int len)
{
	unsigned int tmp_before_read_bytes = *read_bytes;

	lf_arglist->arg_type = 0;

	READ4(*read_bytes, len, lf_arglist->count, leaf_data, ut32);

	lf_arglist->arg_type = (unsigned int *) malloc (lf_arglist->count * 4);
	if (!lf_arglist->arg_type) {
		return 0;
	}
	memcpy (lf_arglist->arg_type, leaf_data, lf_arglist->count * 4);
	leaf_data += (lf_arglist->count * 4);
	*read_bytes += (lf_arglist->count * 4);

	PEEK_READ1 (*read_bytes, len, lf_arglist->pad, leaf_data, ut8);
	PAD_ALIGN (lf_arglist->pad, *read_bytes, leaf_data, len);

	return *read_bytes - tmp_before_read_bytes;
}