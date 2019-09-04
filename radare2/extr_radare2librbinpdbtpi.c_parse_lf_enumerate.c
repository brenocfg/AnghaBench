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
struct TYPE_5__ {int /*<<< orphan*/  fldattr; } ;
struct TYPE_6__ {int /*<<< orphan*/  pad; TYPE_3__ enum_value; TYPE_1__ fldattr; } ;
typedef  TYPE_2__ SLF_ENUMERATE ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_ALIGN (int /*<<< orphan*/ ,unsigned int,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  PEEK_READ1 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ2 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_sval (TYPE_3__*,unsigned char*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  ut16 ; 
 int /*<<< orphan*/  ut8 ; 

__attribute__((used)) static int parse_lf_enumerate(SLF_ENUMERATE *lf_enumerate, unsigned char *leaf_data, unsigned int *read_bytes, unsigned int len)
{
	unsigned int read_bytes_before = 0, tmp_read_bytes_before = 0;

	lf_enumerate->enum_value.name_or_val = 0;

	read_bytes_before = *read_bytes;
	READ2(*read_bytes, len, lf_enumerate->fldattr.fldattr, leaf_data, ut16);

	tmp_read_bytes_before = *read_bytes;
	parse_sval(&lf_enumerate->enum_value, leaf_data, read_bytes, len);
	leaf_data += (*read_bytes - tmp_read_bytes_before);

	PEEK_READ1(*read_bytes, len, lf_enumerate->pad, leaf_data, ut8);
	PAD_ALIGN(lf_enumerate->pad, *read_bytes, leaf_data, len);

//	printf("%s:", "parse_lf_enumerate()");
//	printf_sval_name(&lf_enumerate->enum_value);
//	printf("\n");

	return (*read_bytes - read_bytes_before);
}