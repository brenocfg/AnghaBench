#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmltype ;
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  pg_enc ;
struct TYPE_5__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int parse_xml_decl (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  print_xml_decl (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t strlen (char*) ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_ereport_by_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static char *
xml_out_internal(xmltype *x, pg_enc target_encoding)
{
	char	   *str = text_to_cstring((text *) x);

#ifdef USE_LIBXML
	size_t		len = strlen(str);
	xmlChar    *version;
	int			standalone;
	int			res_code;

	if ((res_code = parse_xml_decl((xmlChar *) str,
								   &len, &version, NULL, &standalone)) == 0)
	{
		StringInfoData buf;

		initStringInfo(&buf);

		if (!print_xml_decl(&buf, version, target_encoding, standalone))
		{
			/*
			 * If we are not going to produce an XML declaration, eat a single
			 * newline in the original string to prevent empty first lines in
			 * the output.
			 */
			if (*(str + len) == '\n')
				len += 1;
		}
		appendStringInfoString(&buf, str + len);

		pfree(str);

		return buf.data;
	}

	xml_ereport_by_code(WARNING, ERRCODE_INTERNAL_ERROR,
						"could not parse XML declaration in stored value",
						res_code);
#endif
	return str;
}