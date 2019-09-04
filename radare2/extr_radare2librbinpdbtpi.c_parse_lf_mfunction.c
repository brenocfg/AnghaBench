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
struct TYPE_3__ {int /*<<< orphan*/  pad; int /*<<< orphan*/  this_adjust; int /*<<< orphan*/  arglist; int /*<<< orphan*/  parm_count; int /*<<< orphan*/  reserved; int /*<<< orphan*/  call_conv; int /*<<< orphan*/  this_type; int /*<<< orphan*/  class_type; int /*<<< orphan*/  return_type; } ;
typedef  TYPE_1__ SLF_MFUNCTION ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_ALIGN (int /*<<< orphan*/ ,unsigned int,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  PEEK_READ1 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ1 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ2 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ4 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st32 ; 
 int /*<<< orphan*/  ut32 ; 
 int /*<<< orphan*/  ut8 ; 

__attribute__((used)) static int parse_lf_mfunction(SLF_MFUNCTION *lf_mfunction, unsigned char *leaf_data, unsigned int *read_bytes, unsigned int len)
{
	unsigned int tmp_before_read_bytes = *read_bytes;

	READ4(*read_bytes, len, lf_mfunction->return_type, leaf_data, ut32);
	READ4(*read_bytes, len, lf_mfunction->class_type, leaf_data, ut32);
	READ4(*read_bytes, len, lf_mfunction->this_type, leaf_data, ut32);
	READ1(*read_bytes, len, lf_mfunction->call_conv, leaf_data, ut8);
	READ1(*read_bytes, len, lf_mfunction->reserved, leaf_data, ut8);
	READ2(*read_bytes, len, lf_mfunction->parm_count, leaf_data, ut8);
	READ4(*read_bytes, len, lf_mfunction->arglist, leaf_data, ut32);
	READ4(*read_bytes, len, lf_mfunction->this_adjust, leaf_data, st32);

	PEEK_READ1(*read_bytes, len, lf_mfunction->pad, leaf_data, ut8);
	PAD_ALIGN(lf_mfunction->pad, *read_bytes, leaf_data, len);

	return *read_bytes - tmp_before_read_bytes;
}