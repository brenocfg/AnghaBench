#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ name_or_val; } ;
struct TYPE_4__ {int /*<<< orphan*/  pad; TYPE_2__ size; int /*<<< orphan*/  index_type; int /*<<< orphan*/  element_type; } ;
typedef  TYPE_1__ SLF_ARRAY ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_ALIGN (int /*<<< orphan*/ ,unsigned int,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  PEEK_READ1 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ4 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_sval (TYPE_2__*,unsigned char*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  ut32 ; 
 int /*<<< orphan*/  ut8 ; 

__attribute__((used)) static int parse_lf_array(SLF_ARRAY *lf_array, unsigned char *leaf_data, unsigned int *read_bytes, unsigned int len)
{
	unsigned int tmp_before_read_bytes = *read_bytes;
	unsigned int before_read_bytes = 0;

	lf_array->size.name_or_val = 0;

	READ4(*read_bytes, len, lf_array->element_type, leaf_data, ut32);
	READ4(*read_bytes, len, lf_array->index_type, leaf_data, ut32);

	before_read_bytes = *read_bytes;
	parse_sval(&lf_array->size, leaf_data, read_bytes, len);
	leaf_data += (*read_bytes - before_read_bytes);

	PEEK_READ1(*read_bytes, len, lf_array->pad, leaf_data, ut8);
	PAD_ALIGN(lf_array->pad, *read_bytes, leaf_data, len);

//	printf("parse_lf_array(): name = ");
//	printf_sval_name(&lf_array->size);
//	printf("\n");
	return *read_bytes - tmp_before_read_bytes;
}