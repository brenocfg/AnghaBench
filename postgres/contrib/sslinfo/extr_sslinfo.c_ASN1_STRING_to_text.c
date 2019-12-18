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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int ASN1_STRFLGS_ESC_MSB ; 
 int ASN1_STRFLGS_RFC2253 ; 
 int ASN1_STRFLGS_UTF8_CONVERT ; 
 int /*<<< orphan*/  ASN1_STRING_print_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_CLOSE ; 
 int BIO_free (int /*<<< orphan*/ *) ; 
 size_t BIO_get_mem_data (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PG_RETURN_TEXT_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PG_UTF8 ; 
 int /*<<< orphan*/ * cstring_to_text (char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* pg_any_to_server (char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Datum
ASN1_STRING_to_text(ASN1_STRING *str)
{
	BIO		   *membuf;
	size_t		size;
	char		nullterm;
	char	   *sp;
	char	   *dp;
	text	   *result;

	membuf = BIO_new(BIO_s_mem());
	if (membuf == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("could not create OpenSSL BIO structure")));
	(void) BIO_set_close(membuf, BIO_CLOSE);
	ASN1_STRING_print_ex(membuf, str,
						 ((ASN1_STRFLGS_RFC2253 & ~ASN1_STRFLGS_ESC_MSB)
						  | ASN1_STRFLGS_UTF8_CONVERT));
	/* ensure null termination of the BIO's content */
	nullterm = '\0';
	BIO_write(membuf, &nullterm, 1);
	size = BIO_get_mem_data(membuf, &sp);
	dp = pg_any_to_server(sp, size - 1, PG_UTF8);
	result = cstring_to_text(dp);
	if (dp != sp)
		pfree(dp);
	if (BIO_free(membuf) != 1)
		elog(ERROR, "could not free OpenSSL BIO structure");

	PG_RETURN_TEXT_P(result);
}