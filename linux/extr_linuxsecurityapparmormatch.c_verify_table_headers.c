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
struct table_header {size_t td_lolen; } ;

/* Variables and functions */
 scalar_t__ ACCEPT1_FLAGS (int) ; 
 scalar_t__ ACCEPT2_FLAGS (int) ; 
 int EPROTO ; 
 size_t YYTD_ID_ACCEPT ; 
 size_t YYTD_ID_ACCEPT2 ; 
 size_t YYTD_ID_BASE ; 
 size_t YYTD_ID_CHK ; 
 size_t YYTD_ID_DEF ; 
 size_t YYTD_ID_EC ; 
 size_t YYTD_ID_NXT ; 

__attribute__((used)) static int verify_table_headers(struct table_header **tables, int flags)
{
	size_t state_count, trans_count;
	int error = -EPROTO;

	/* check that required tables exist */
	if (!(tables[YYTD_ID_DEF] && tables[YYTD_ID_BASE] &&
	      tables[YYTD_ID_NXT] && tables[YYTD_ID_CHK]))
		goto out;

	/* accept.size == default.size == base.size */
	state_count = tables[YYTD_ID_BASE]->td_lolen;
	if (ACCEPT1_FLAGS(flags)) {
		if (!tables[YYTD_ID_ACCEPT])
			goto out;
		if (state_count != tables[YYTD_ID_ACCEPT]->td_lolen)
			goto out;
	}
	if (ACCEPT2_FLAGS(flags)) {
		if (!tables[YYTD_ID_ACCEPT2])
			goto out;
		if (state_count != tables[YYTD_ID_ACCEPT2]->td_lolen)
			goto out;
	}
	if (state_count != tables[YYTD_ID_DEF]->td_lolen)
		goto out;

	/* next.size == chk.size */
	trans_count = tables[YYTD_ID_NXT]->td_lolen;
	if (trans_count != tables[YYTD_ID_CHK]->td_lolen)
		goto out;

	/* if equivalence classes then its table size must be 256 */
	if (tables[YYTD_ID_EC] && tables[YYTD_ID_EC]->td_lolen != 256)
		goto out;

	error = 0;
out:
	return error;
}