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
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_to_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int NID_undef ; 
 int OBJ_txt2nid (char*) ; 
 int /*<<< orphan*/ * X509_NAME_ENTRY_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_get_entry (int /*<<< orphan*/ *,int) ; 
 int X509_NAME_get_index_by_NID (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Datum
X509_NAME_field_to_text(X509_NAME *name, text *fieldName)
{
	char	   *string_fieldname;
	int			nid,
				index;
	ASN1_STRING *data;

	string_fieldname = text_to_cstring(fieldName);
	nid = OBJ_txt2nid(string_fieldname);
	if (nid == NID_undef)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("invalid X.509 field name: \"%s\"",
						string_fieldname)));
	pfree(string_fieldname);
	index = X509_NAME_get_index_by_NID(name, nid, -1);
	if (index < 0)
		return (Datum) 0;
	data = X509_NAME_ENTRY_get_data(X509_NAME_get_entry(name, index));
	return ASN1_STRING_to_text(data);
}