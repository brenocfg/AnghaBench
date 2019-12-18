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
typedef  int uint16 ;
typedef  int /*<<< orphan*/  bytea ;
typedef  int /*<<< orphan*/  Page ;

/* Variables and functions */
 int BLCKSZ ; 
 int BrinPageType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ *) ; 
 int VARHDRSZ ; 
 int VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int,int) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 

__attribute__((used)) static Page
verify_brin_page(bytea *raw_page, uint16 type, const char *strtype)
{
	Page		page;
	int			raw_page_size;

	raw_page_size = VARSIZE(raw_page) - VARHDRSZ;

	if (raw_page_size != BLCKSZ)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("input page too small"),
				 errdetail("Expected size %d, got %d",
						   BLCKSZ, raw_page_size)));

	page = VARDATA(raw_page);

	/* verify the special space says this page is what we want */
	if (BrinPageType(page) != type)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("page is not a BRIN page of type \"%s\"", strtype),
				 errdetail("Expected special type %08x, got %08x.",
						   type, BrinPageType(page))));

	return page;
}