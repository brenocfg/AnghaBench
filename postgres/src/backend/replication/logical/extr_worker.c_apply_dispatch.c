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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  apply_handle_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_handle_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_handle_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_handle_insert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_handle_origin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_handle_relation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_handle_truncate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_handle_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_handle_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char) ; 
 char pq_getmsgbyte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
apply_dispatch(StringInfo s)
{
	char		action = pq_getmsgbyte(s);

	switch (action)
	{
			/* BEGIN */
		case 'B':
			apply_handle_begin(s);
			break;
			/* COMMIT */
		case 'C':
			apply_handle_commit(s);
			break;
			/* INSERT */
		case 'I':
			apply_handle_insert(s);
			break;
			/* UPDATE */
		case 'U':
			apply_handle_update(s);
			break;
			/* DELETE */
		case 'D':
			apply_handle_delete(s);
			break;
			/* TRUNCATE */
		case 'T':
			apply_handle_truncate(s);
			break;
			/* RELATION */
		case 'R':
			apply_handle_relation(s);
			break;
			/* TYPE */
		case 'Y':
			apply_handle_type(s);
			break;
			/* ORIGIN */
		case 'O':
			apply_handle_origin(s);
			break;
		default:
			ereport(ERROR,
					(errcode(ERRCODE_PROTOCOL_VIOLATION),
					 errmsg("invalid logical replication message type \"%c\"", action)));
	}
}