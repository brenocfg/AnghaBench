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
struct TYPE_3__ {int /*<<< orphan*/  substructs; } ;
typedef  TYPE_1__ SLF_FIELDLIST ;
typedef  int ELeafType ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_LF2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  READ2 (unsigned int,unsigned int,int,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLF_ENUMERATE ; 
 int /*<<< orphan*/  SLF_MEMBER ; 
 int /*<<< orphan*/  SLF_METHOD ; 
 int /*<<< orphan*/  SLF_NESTTYPE ; 
 int /*<<< orphan*/  SLF_ONEMETHOD ; 
#define  eLF_ENUMERATE 132 
#define  eLF_MEMBER 131 
#define  eLF_METHOD 130 
#define  eLF_NESTTYPE 129 
#define  eLF_ONEMETHOD 128 
 int /*<<< orphan*/  lf_enumerate ; 
 int /*<<< orphan*/  lf_member ; 
 int /*<<< orphan*/  lf_method ; 
 int /*<<< orphan*/  lf_nesttype ; 
 int /*<<< orphan*/  lf_onemethod ; 
 int /*<<< orphan*/  r_list_new () ; 
 int /*<<< orphan*/  ut16 ; 

__attribute__((used)) static int parse_lf_fieldlist(SLF_FIELDLIST *lf_fieldlist,  unsigned char *leaf_data, unsigned int *read_bytes, unsigned int len)
{
	ELeafType leaf_type;
	int curr_read_bytes = 0;
	unsigned char *p = leaf_data;

	lf_fieldlist->substructs = r_list_new ();

	while (*read_bytes <= len) {
		READ2(*read_bytes, len, leaf_type, p, ut16);
		switch (leaf_type) {
		case eLF_ENUMERATE:
			PARSE_LF2(SLF_ENUMERATE, lf_enumerate, eLF_ENUMERATE);
			break;
		case eLF_NESTTYPE:
			PARSE_LF2(SLF_NESTTYPE, lf_nesttype, eLF_NESTTYPE);
			break;
		case eLF_METHOD:
			PARSE_LF2(SLF_METHOD, lf_method, eLF_METHOD);
			break;
		case eLF_MEMBER:
			PARSE_LF2(SLF_MEMBER, lf_member, eLF_MEMBER);
			break;
		case eLF_ONEMETHOD:
			PARSE_LF2(SLF_ONEMETHOD, lf_onemethod, eLF_ONEMETHOD);
			break;
		default:
//			printf("unsupported leaf type in parse_lf_fieldlist()\n");
			return 0;
		}

		if (curr_read_bytes != 0) {
			p += curr_read_bytes;
		} else {
			return 0;
		}
	}
	return 0;
}