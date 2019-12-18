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
struct TYPE_5__ {scalar_t__ name; } ;
struct TYPE_4__ {TYPE_2__ name; int /*<<< orphan*/  index; int /*<<< orphan*/  pad; } ;
typedef  TYPE_1__ SLF_NESTTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  READ2 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ4 (unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_sctring (TYPE_2__*,unsigned char*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  ut16 ; 

__attribute__((used)) static int parse_lf_nesttype(SLF_NESTTYPE *lf_nesttype, unsigned char *leaf_data, unsigned int *read_bytes, unsigned int len)
{
	unsigned int read_bytes_before = *read_bytes;

	lf_nesttype->name.name = 0;

	READ2(*read_bytes, len, lf_nesttype->pad, leaf_data, ut16);
	READ4(*read_bytes, len, lf_nesttype->index, leaf_data, ut16);

	parse_sctring(&lf_nesttype->name, leaf_data, read_bytes, len);
//	printf("parse_lf_nesttype(): name = %s\n", lf_nesttype->name.name);

	return *read_bytes - read_bytes_before;
}