#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ name_or_val; } ;
struct TYPE_5__ {int /*<<< orphan*/  cv_property; } ;
struct TYPE_6__ {int /*<<< orphan*/  pad; TYPE_3__ size; TYPE_1__ prop; int /*<<< orphan*/  vshape; int /*<<< orphan*/  derived; int /*<<< orphan*/  field_list; int /*<<< orphan*/  count; } ;
typedef  TYPE_2__ SLF_STRUCTURE ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_ALIGN (int /*<<< orphan*/ ,unsigned int,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  PEEK_READ1 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ2 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ4 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWAP_UINT16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_sval (TYPE_3__*,unsigned char*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  ut16 ; 
 int /*<<< orphan*/  ut32 ; 
 int /*<<< orphan*/  ut8 ; 

__attribute__((used)) static int parse_lf_structure(SLF_STRUCTURE *lf_structure, unsigned char *leaf_data, unsigned int *read_bytes, unsigned int len)
{
//	SLF_STRUCTURE lf_structure;
	unsigned int tmp_before_read_bytes = *read_bytes;
	unsigned int before_read_bytes = 0;

	lf_structure->size.name_or_val = 0;

	READ2(*read_bytes, len, lf_structure->count, leaf_data, ut16);
	READ2(*read_bytes, len, lf_structure->prop.cv_property, leaf_data, ut16);
	READ4(*read_bytes, len, lf_structure->field_list, leaf_data, ut32);
	READ4(*read_bytes, len, lf_structure->derived, leaf_data, ut32);
	READ4(*read_bytes, len, lf_structure->vshape, leaf_data, ut32);

	lf_structure->prop.cv_property = SWAP_UINT16(lf_structure->prop.cv_property);

	before_read_bytes = *read_bytes;
	parse_sval(&lf_structure->size, leaf_data, read_bytes, len);
	leaf_data += (*read_bytes - before_read_bytes);

	PEEK_READ1(*read_bytes, len, lf_structure->pad, leaf_data, ut8);
	PAD_ALIGN(lf_structure->pad, *read_bytes, leaf_data, len);

//	printf("parse_lf_structure(): name = ");
//	printf_sval_name(&lf_structure->size);
//	printf("\n");
	return *read_bytes - tmp_before_read_bytes;
}